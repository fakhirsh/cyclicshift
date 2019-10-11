
#include "Log.hpp"

#include "../System/App.hpp"
#include "../Utility/String.hpp"

using namespace FEngine;

using namespace std;

namespace FEngine
{
    
    Log::Log()
    {
    
    }
    
    Log::~Log()
    {
    
    }
    
    bool Log::Init ()
    {
        return true;
    }
    
    void Log::Print (string message, string functionName, int lineNo)
    {
        App * gApp = App::Get();
        int elapsedTimeINT = gApp->GetElapsedTime();
        int sec = elapsedTimeINT % 60;
        elapsedTimeINT /= 60;
        int min = elapsedTimeINT % 60;
        
        string elapsedTimeStr = string("m:") + String::ToString(min) + string(" s:") + String::ToString(sec);
        string newStr = string("[FEngine|") + elapsedTimeStr + string("]  ") + message;
        if(functionName != "")
        {
            newStr += string(" {Fn:") + functionName;
            
            if (lineNo != -1) {
                newStr += string(" - Line:") + String::ToString(lineNo);
            }
            newStr += string("}");
        }
        
        newStr += "\n";
        
        PrintToConsole(newStr);
        //PrintToMemory(newStr);
    }
    
    void Log::PrintToXML (std::string message)
    {
    
    }
    
    void Log::PrintToMemory (std::string message)
    {
        _memoryLog += message;
    }
   
    

}
