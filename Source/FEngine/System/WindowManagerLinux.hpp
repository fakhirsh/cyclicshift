#pragma once

#include "WindowManager.hpp"

class GLFWwindow;
    
namespace FEngine
{   

    class WindowManagerLinux : public WindowManager
    {
        public:
            WindowManagerLinux();
            virtual ~WindowManagerLinux();
            
            virtual bool Initialize(int width, int height, std::string title, std::string className);
            virtual void Shutdown();
            
        private:
            GLFWwindow * _window;


    };
    
}