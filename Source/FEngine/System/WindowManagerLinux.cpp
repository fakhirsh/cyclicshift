
#include "WindowManagerLinux.hpp"
#include "../System/App.hpp"
#include "../Debugging/Log.hpp"
#include "../Utility/String.hpp"

#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace std;
using namespace std::chrono;

namespace FEngine{

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
            case GLFW_KEY_X:
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

    void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        int mappedKey = MapKey(key);
        int mappedAction = MapAction(action);
        _kbDelegate(mappedKey, mappedAction);
    }

    void _cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        _mousePosDelegate(xpos, ypos);
    }

    void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

/*        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){*/
            //App::Get()->GetLogger()->Print("Left mouse button pressed");
        //}
        //else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
            //App::Get()->GetLogger()->Print("Left mouse button released");
        /*}*/
        int mappedButton = MapMouseButton(button);
        int mappedAction = MapAction(action);
        _mouseBtnDelegate(mappedButton, mappedAction, xpos, ypos);
    }

    WindowManagerLinux::WindowManagerLinux(){
        // So why is glClearColor doing here in a TOTALLY unrelated
        //   function / file? Well because compiler gives me linker
        //   errors if I remove every single GL command from this
        //   file (which actually should be the case!!!)
        glClearColor(1.0f, 0.0f, 0.4f, 0.0f);

        _window = NULL;
    }

    WindowManagerLinux::~WindowManagerLinux(){

    }

    bool WindowManagerLinux::Initialize(int width, int height, std::string title, std::string className){

        // Initialise GLFW
        if( !glfwInit() )
        {
            App::Get()->GetLogger()->Print("Failed to initialize GLFW", "WindowManagerLinux::Initialize");
            return false;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // Open a window and create its OpenGL context
        _window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL);
        if( _window == NULL ){
            App::Get()->GetLogger()->Print("Failed to open GLFW window. v3.3 is not compatible with Intel GPU. Try v2.1", "WindowManagerLinux::Initialize");
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent((GLFWwindow *)_window);

        // Initialize GLEW
        glewExperimental = true; // Needed for core profile
        if (glewInit() != GLEW_OK) {
            App::Get()->GetLogger()->Print("Failed to initialize GLEW");
            glfwTerminate();
            return false;
        }

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetKeyCallback(_window, _key_callback);
        glfwSetCursorPosCallback(_window, _cursor_position_callback);
        glfwSetMouseButtonCallback(_window, _mouse_button_callback);

        //glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        return true;

    }

    void WindowManagerLinux::MainLoop(){
        long int time = 0;
        static long int prev_time = 0;

        do{

            time = high_resolution_clock::now().time_since_epoch().count();
            const long int num = high_resolution_clock::period::num;
            const long int den = high_resolution_clock::period::den;
            float dt = (time - prev_time) * 1.0 * num / den;


/*            double xpos, ypos;*/
            //glfwGetCursorPos(_window, &xpos, &ypos);
            /*App::Get()->GetLogger()->Print("X: " + String::ToString(xpos) + " -- Y: " + String::ToString(ypos));*/

            // Tick function from the App class:
            _tickDelegate(dt);

            prev_time = time;

            // Swap buffers
            glfwSwapBuffers(_window);
		    glfwPollEvents();
        }
        while( glfwGetKey(_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                       glfwWindowShouldClose(_window) == 0 );


    }


    void WindowManagerLinux::Resize(int newWidth, int newHeight){
        App::Get()->GetLogger()->Print("Resizeing window...");
    }

    void WindowManagerLinux::Shutdown(){
       	glfwTerminate();
    }


    void WindowManagerLinux::SetInputCallbacks(MouseBtnDelegate mbd, MousePosDelegate mpd, KBDelegate kbd){
        _mouseBtnDelegate = mbd;
        _mousePosDelegate = mpd;
        _kbDelegate = kbd;
    }

    void WindowManagerLinux::SetTickCallback(TickDelegate td){
         _tickDelegate = td;
    }
}
