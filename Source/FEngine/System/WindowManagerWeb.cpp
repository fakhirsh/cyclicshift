
#include "WindowManagerWeb.hpp"
#include <GL/glfw.h>
#include <emscripten/emscripten.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

namespace FEngine{
   
    // Global delegate pointer for "Tick" method. Why?
    // Because I can only pass void Fn(void) as the signature
    // for main loop function pointer. So this is a hack:
    TickDelegate gtd;

    WindowManagerWeb::WindowManagerWeb(){
    
    }
    WindowManagerWeb::~WindowManagerWeb(){
    
    }

    bool WindowManagerWeb::Initialize(int width, int height, std::string title, std::string className){
        if (glfwInit() != GL_TRUE)
        {
            cout << "WindowManagerWeb::glfwInit() failed" << endl;
            return false;
        }

        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_DEPTH_BUFFER_BIT);
        //glDisable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        // Open window
        int ok = glfwOpenWindow(
                            width, height,          // Width and height of window
                            8, 8, 8,           // Number of red, green, and blue bits for color buffer
                            8,                 // Number of bits for alpha buffer
                            16,                // Number of bits for depth buffer (Z-buffer)
                            0,                 // Number of bits for stencil buffer
                            GLFW_WINDOW        // We want a desktop window (could be GLFW_FULLSCREEN)
                            );

        if (ok != GL_TRUE)
        {
            cout << "WindowManagerWEB::glfwOpenWindow() failed" << endl;
            return false;
        }

        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_DEPTH_BUFFER_BIT);

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
        gtd(dt);

        prev_time = time;

        glfwSwapBuffers();
    }

    void WindowManagerWeb::MainLoop(TickDelegate td){
        gtd = td;
        emscripten_set_main_loop(GlobalTick, 0, 1);
    }

}
