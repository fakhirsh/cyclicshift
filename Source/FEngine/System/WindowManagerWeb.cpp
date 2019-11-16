
#include "WindowManagerWeb.hpp"
#include <GL/glfw.h>
#include <emscripten/emscripten.h>
#include <iostream>
#include <chrono>

#include <System/App.hpp>
#include <Debugging/Log.hpp>

using namespace std;
using namespace chrono;

namespace FEngine{
   
    // Global delegate pointer for "Tick" method. Why?
    // Because I can only pass void Fn(void) as the signature
    // for main loop function pointer. So this is a hack:
    TickDelegate _tickDelegate;
    MouseBtnDelegate _mouseBtnDelegate;
    MousePosDelegate _mousePosDelegate;
    KBDelegate _kbDelegate;

     /*
     * Map the GLFW key code to FEngine's native key code
     */
    unsigned int MapAction(int action){
        switch(action){
            case GLFW_PRESS:
                return INPUT::KEY_PRESS;
                break;
            case GLFW_RELEASE:
                return INPUT::KEY_RELEASE;
                break;
            default:
                break;
        }
        return -1;
    }

    unsigned int MapKey(int code){
        switch(code){
            case GLFW_KEY_UP:
                return INPUT::KB_UP;
                break;
            case GLFW_KEY_DOWN:
                return INPUT::KB_DOWN;
                break;
            case GLFW_KEY_LEFT:
                return INPUT::KB_LEFT;
                break;
            case GLFW_KEY_RIGHT:
                return INPUT::KB_RIGHT;
                break;
            case GLFW_KEY_SPACE:
                return INPUT::KB_SPACE;
                break;
            case 'X':
            case 'x':
                return INPUT::KB_X;
                break;
            default:
                break;
        }
        return -1;
    }

    unsigned int MapMouseButton(int button){
        switch(button){
            case GLFW_MOUSE_BUTTON_LEFT:
                return INPUT::MOUSE_BUTTON_LEFT;
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                return INPUT::MOUSE_BUTTON_RIGHT;
                break;
            default:
                break;
        }
        return -1;
    }
   void _key_callback(int key, int action)
    {
        int mappedKey = MapKey(key);
        int mappedAction = MapAction(action);
        _kbDelegate(mappedKey, mappedAction);
    }
   
    void _cursor_position_callback(int xpos, int ypos)
    {
        _mousePosDelegate(xpos, ypos);
    }

    void _mouse_button_callback(int button, int action)
    {
        int xpos, ypos;
        glfwGetMousePos(&xpos, &ypos);
        int mappedButton = MapMouseButton(button);
        int mappedAction = MapAction(action);
        _mouseBtnDelegate(mappedButton, mappedAction, xpos, ypos);
    }


    WindowManagerWeb::WindowManagerWeb(){
    
    }
    WindowManagerWeb::~WindowManagerWeb(){
    
    }

    bool WindowManagerWeb::Initialize(int width, int height, std::string title, std::string className){
        LogPtr log = App::Get()->GetLogger();

        if (glfwInit() != GL_TRUE)
        {
            log->Print("WindowManagerWeb::glfwInit() failed");
            return false;
        }

        // Open window
        int ok = glfwOpenWindow(
                            width, height,          // Width and height of window
                            8, 8, 8,           // Number of red, green, and blue bits for color buffer
                            8,                 // Number of bits for alpha buffer
                            16,                // Number of bits for depth buffer (Z-buffer)
                            0,                 // Number of bits for stencil buffer
                            GLFW_FULLSCREEN        // We want a desktop window (could be GLFW_FULLSCREEN)
                            );

        if (ok != GL_TRUE)
        {
            log->Print("WindowManagerWEB::glfwOpenWindow() failed");
            return false;
        }

        //glfwSetInputMode(GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetKeyCallback(_key_callback);
        glfwSetMousePosCallback(_cursor_position_callback);
        glfwSetMouseButtonCallback( _mouse_button_callback);
        //glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        return true;

    }

    void WindowManagerWeb::Shutdown(){
        glfwTerminate();
    }

   // Ugly hack for Emscipten main loop setup: 
    void GlobalTick(){
        long int time = 0;
        static long int prev_time = 0;
 
        time = high_resolution_clock::now().time_since_epoch().count();
        const long int num = high_resolution_clock::period::num;
        const long int den = high_resolution_clock::period::den;
        float dt = (time - prev_time) * 1.0 * num / den;
     
        // Tick function from the App class: 
        _tickDelegate(dt);

        prev_time = time;

        glfwSwapBuffers();
    }

    void WindowManagerWeb::MainLoop(){
        emscripten_set_main_loop(GlobalTick, 0, 1);
    }

    void WindowManagerWeb::Resize(int newWidth, int newHeight){
         
    }

    void WindowManagerWeb::SetInputCallbacks(MouseBtnDelegate mbd, MousePosDelegate mpd, KBDelegate kbd){
        _mouseBtnDelegate = mbd;
        _mousePosDelegate = mpd;
        _kbDelegate = kbd;
    }
    
    void WindowManagerWeb::SetTickCallback(TickDelegate td){
        _tickDelegate = td;
    }

}
