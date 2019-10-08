#pragma once

#include <string>

namespace FEngine
{
    
    class WindowManager
    {
        public:
            
            virtual bool Initialize(int width, int height, std::string title, std::string className) = 0;
            
            virtual void Shutdown() = 0;

        private:
   };
    
}
