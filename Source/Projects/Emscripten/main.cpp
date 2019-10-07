

//#include <stdlib.h>
#include <iostream>
#include <fstream>
//#include <GL/glfw.h>
//#include <emscripten/emscripten.h>
#include <System/App.hpp>
#include <ResourceCache/IOManagerDefault.hpp>


//#include "EMCGlue.h"

/*
bool InitGLFW();
void Tick();
void ShutdownGLFW();

void OnMouseClick(int button, int action);
void OnMouseMove(int x, int y);

const int width = 960;
const int height = 640;
*/

using namespace std;
using namespace FEngine;

int main()
{
/*
    ifstream in("Data/debug.txt");
    if(!in){
        cout << "Error opening debug.txt" << endl;
        return -1;
    }

    string s;
    in >> s;
    cout << s << endl;

    cout << "Hello from Emscripten !!!" << endl;
*/  
  
    App * app = App::Get();

    app->SetIOManager(new IOManagerDefault());

    app->Initialize("Data/");


    /*
    if (InitGLFW() == true)
    {
        printf("main.cpp:InitGLFW() success...\n");
        emscripten_set_main_loop(Tick, 0, 1);
    }
    
    ShutdownGLFW();
    */
    return 0;
}
/*
bool InitGLFW()
{
    if (glfwInit() != GL_TRUE)
    {
        printf("main.cpp:glfwInit() failed\n");
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
        printf("main.cpp:glfwOpenWindow() failed\n");
        return false;
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_BUFFER_BIT);
    
    glfwSetMousePosCallback(OnMouseMove);
    glfwSetMouseButtonCallback(OnMouseClick);
    
//    if(!EMCGlue::Init(width, height))
//    {
//        printf("EMCGlue.cpp:Init() failed\n");
//        return false;
//    }
    
    return true;
}

void Tick()
{
//    EMCGlue::Tick();
    
    glfwSwapBuffers();
}

void ShutdownGLFW()
{
//    EMCGlue::Shutdown();
    
    glfwTerminate();
}

void OnMouseClick(int button, int action)
{
    int x, y;
    glfwGetMousePos(&x, &y);

    if(action == GLFW_PRESS)
    {
        //printf("Mouse button %i has been pressed\n", button);
//        EMCGlue::MouseDown(x, height - y);
    }
    if(action == GLFW_RELEASE)
    {
        //printf("Mouse button %i has been released\n", button);
//        EMCGlue::MouseUp(x, height - y);
    }
}

void OnMouseMove(int x, int y)
{
    int lState = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);
    if (lState == GLFW_PRESS)
    {
        //printf("Dragged %i to %i %i\n", GLFW_MOUSE_BUTTON_LEFT, x, y);
//        EMCGlue::MouseMoved(x, height - y);
    }
    if(lState == GLFW_RELEASE)
    {
        //printf("Moved %i to %i %i\n", GLFW_MOUSE_BUTTON_LEFT, x, y);
    }
}
*/
