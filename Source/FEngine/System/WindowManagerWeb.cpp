
#include "WindowManagerWeb.hpp"
#include <GL/glfw.h>
#include <emscripten/emscripten.h>
#include <iostream>

using namespace std;

namespace FEngine{
    
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

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_BUFFER_BIT);


        return true;

    }

    void WindowManagerWeb::Shutdown(){
    
    }


}
