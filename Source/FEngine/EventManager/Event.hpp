
#pragma once

#include <string>
#include <map>

using namespace std;

namespace FEngine{

    typedef string EventType;

    /*
     * The Event object. Right now event type is a string. A dictionary of
     *   arguments with key as string and values as ONLY doubles.
     */

    class Event{
        public:
            Event();
            ~Event();
            
            void SetArg(string key, double value); 
            double GetArg(string key);

            void SetEventType(const EventType & type);
            EventType GetEventType();

            void SetEventName(const string & name);
            string GetEventName();

        private: 
            EventType _eventType;
            string _eventName;
            map<string, double> _args;
    };

};
