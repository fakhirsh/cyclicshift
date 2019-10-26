
#pragma once

#include <Delegate.hpp>
#include <map>
#include <list>
#include <string>

#include "Event.hpp"

using namespace CppDelegates;
using namespace std;

namespace FEngine{
    
    const int NUM_EVENT_QUEUES = 2;

    typedef shared_ptr<Event> EventPtr;
    typedef CppDelegates::delegate<void (const EventPtr &)> EventDelegate;
    typedef list<EventDelegate> DelegateList;

    class EventManager{
        public:
            EventManager();
            ~EventManager();
            
            bool AddListener(EventType eventType, EventDelegate eventDelegate);
            bool RemoveListener(EventType eventType, EventDelegate eventDelegate);
            void EnQueue(EventPtr e);
            void Update(float dt);

        private:

            list<EventPtr> _eventQueue[NUM_EVENT_QUEUES];
            int _activeQueue;
            map<EventType, DelegateList> _listenerMap;
    };

};
