
#include "Event.hpp"

namespace FEngine{

    Event::Event(){
        _eventType = "invalid";
        _eventName = "invalid";
    }
    
    Event::~Event(){
    
    }
    
    void Event::SetArg(string key, double value){
        _args[key] = value;
    }
    
    double Event::GetArg(string key){
        return _args[key];
    }

    void Event::SetEventType(const string & type){
        _eventType = type;
    }
    
    string Event::GetEventType(){
        return _eventType;
    }

    void Event::SetEventName(const string & name){
        _eventName = name;
    }
    
    string Event::GetEventName(){
        return _eventName;
    }

};
