
#include "WindowManagerLinux.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

namespace FEngine{

    WindowManagerLinux::WindowManagerLinux(){
        _window = NULL;
    }
    
    WindowManagerLinux::~WindowManagerLinux(){
    
    }
    
    bool WindowManagerLinux::Initialize(int width, int height, std::string title, std::string className){
       // Initialise GLFW
        if( !glfwInit() )
        {
            cout << "Failed to initialize GLFW" << endl;
            return false;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        
        // Open a window and create its OpenGL context
        _window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL);
        if( _window == NULL ){
            cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials." << endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent((GLFWwindow *)_window);

        // Initialize GLEW
        glewExperimental = true; // Needed for core profile
        if (glewInit() != GLEW_OK) {
            cout << "Failed to initialize GLEW" << endl;
            glfwTerminate();
            return false;
        }

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

        // Dark blue background
        //glClearColor(1.0f, 0.0f, 0.4f, 0.0f);

        //do{
        
        //} 
        //while( glfwGetKey(_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        //               glfwWindowShouldClose(_window) == 0 );



        return true;
 
    }
    
    void WindowManagerLinux::Shutdown(){
       	glfwTerminate(); 
    }

}
