#pragma once

#include <string>
#include "../../3rdParty/FastDelegate/FastDelegate.h"

namespace FEngine
{
    class App;
    typedef fastdelegate::FastDelegate1<float> TickDelegate; 

    class WindowManager
    {
        public:
            
            virtual bool Initialize(int width, int height, std::string title, std::string className) = 0;
            virtual void Shutdown() = 0;
            
            virtual void MainLoop(TickDelegate td) = 0;

        private:
   };
    
}
