
#pragma once

#include "Log.h"

#include <string>

namespace FEngine
{
    class LogStub : public Log
    {
    public:
        LogStub();
        virtual ~LogStub();
        
    private:
        virtual void    PrintToConsole  (std::string message);
        virtual void    PrintToNetwork  (std::string message);
        
    };
}
