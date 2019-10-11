#pragma once

#include "WindowManager.hpp"

class GLFWwindow;
    
namespace FEngine
{   

    class WindowManagerWeb : public WindowManager
    {
        public:
            WindowManagerWeb();
            virtual ~WindowManagerWeb();
            
            virtual bool Initialize(int width, int height, std::string title, std::string className);
            virtual void Shutdown();
            
            virtual void MainLoop(TickDelegate td);
                        
        private:
            GLFWwindow * _window;


    };
    
}
