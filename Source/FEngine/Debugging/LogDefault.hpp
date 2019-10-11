
#pragma once

#include "Log.hpp"

#include <string>

namespace FEngine
{
    class LogDefault : public Log
    {
    public:
        LogDefault();
        virtual ~LogDefault();
        
    private:
        virtual void    PrintToConsole  (std::string message);
        virtual void    PrintToNetwork  (std::string message);

    };
}
