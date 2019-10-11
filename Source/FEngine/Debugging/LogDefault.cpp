
#include "LogDefault.hpp"

#include <iostream>

using namespace std;

namespace FEngine
{

    LogDefault::LogDefault ()
    {
    
    }
    
    LogDefault::~LogDefault ()
    {
    
    }
        
    void LogDefault::PrintToConsole (std::string message)
    {
        cout << message;
    }
    
    void LogDefault::PrintToNetwork  (std::string message)
    {
        // SendToNetwork(message);
    }
}
