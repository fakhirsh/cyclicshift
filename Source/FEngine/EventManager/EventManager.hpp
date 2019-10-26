
#pragma once

#include "../../3rdParty/CppDelegates/Delegate.hpp"
#include <map>
#include <list>
#include <string>

#include "Event.hpp"

using namespace CppDelegates;
using namespace std;

namespace FEngine{
    
    const int NUM_EVENT_QUEUES = 2;

    typedef CppDelegates::delegate<void (Event)> EventDelegate;
    typedef list<EventDelegate> DelegateList;
    
    class EventManager{
        public:
            EventManager();
            ~EventManager();
            
            bool AddListener(EventType eventType, EventDelegate eventDelegate);
            bool RemoveListener(EventType eventType, EventDelegate eventDelegate);
            void EnQueue(Event e);
            void Update(float dt);

        private:

            list<Event> _eventQueue[NUM_EVENT_QUEUES];
            int _activeQueue;
            map<EventType, DelegateList> _listenerMap;
    };

};
