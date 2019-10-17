
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


     void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_E && action == GLFW_PRESS){
            //App::Get()->GetLogger()->Print("E key Pressed");
        }
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
            App::Get()->GetLogger()->Print("Failed to initialize GLFW", "WindowManagerLinux::Initialize", 24);
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

        return true;
 
    }

    void WindowManagerLinux::MainLoop(TickDelegate tickDelegate){
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
            tickDelegate(dt);

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

    

}
