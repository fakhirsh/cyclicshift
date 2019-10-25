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

            virtual void MainLoop();

            virtual void Resize(int newWidth, int newHeight);

            virtual void SetInputCallbacks(MouseBtnDelegate mbd, MousePosDelegate mpd, KBDelegate kbd);
            virtual void SetTickCallback(TickDelegate td);

        private:

            GLFWwindow * _window;

    };
    
}
