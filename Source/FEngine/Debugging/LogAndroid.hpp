
#pragma once

#include "Log.h"

#include <string>

namespace FEngine
{
    class LogAndroid : public Log
    {
    public:
        LogAndroid();
        virtual ~LogAndroid();
        
    private:
        virtual void    PrintToConsole  (std::string message);
        virtual void    PrintToNetwork  (std::string message);
        
    };
}
