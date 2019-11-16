#pragma once

#include <string>
//#include "../../3rdParty/FastDelegate/FastDelegate.h"
#include "../../3rdParty/CppDelegates/Delegate.hpp"
//#include <Delegate.hpp>

namespace FEngine
{
    class App;
    /*typedef fastdelegate::FastDelegate1<float> TickDelegate;*/
    //typedef fastdelegate::FastDelegate4<int, int, double, double> MouseBtnDelegate;
    //typedef fastdelegate::FastDelegate2<double, double> MousePosDelegate;
    /*typedef fastdelegate::FastDelegate2<int, int> KBDelegate;*/

    typedef CppDelegates::delegate<void (float)> TickDelegate;
    typedef CppDelegates::delegate<void (int, int, double, double)> MouseBtnDelegate;
    typedef CppDelegates::delegate<void (double, double)> MousePosDelegate;
    typedef CppDelegates::delegate<void (int, int)> KBDelegate;
    
    class WindowManager
    {
        public:
            
            virtual bool Initialize(int width, int height, std::string title, std::string className) = 0;
            virtual void Shutdown() = 0;
            
            virtual void MainLoop() = 0;

            virtual void Resize(int newWidth, int newHeight) = 0;

            virtual void SetInputCallbacks(MouseBtnDelegate mbd, MousePosDelegate mpd, KBDelegate kbd) = 0;
            virtual void SetTickCallback(TickDelegate td) = 0;

        private:
   };
    
}
