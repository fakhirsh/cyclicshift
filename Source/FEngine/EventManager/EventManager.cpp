
#include "EventManager.hpp"
#include "Event.hpp"

#include <iostream>

using namespace std;

namespace FEngine{

    EventManager::EventManager(){
        _activeQueue = 0;
    }

    EventManager::~EventManager(){

    }

    bool EventManager::AddListener(EventType eventType, EventDelegate eventDelegate){
        // This will find OR create a new entry in case if it is not alreasy present
        DelegateList & dlist = _listenerMap[eventType];

        for(auto it = dlist.begin(); it != dlist.end(); ++it){
            if(eventDelegate == (*it)){
                cout << "ERROR: Re-adding a listener..." << endl;
                return false;
            }
        }
        dlist.push_back(eventDelegate);
        return true;
    }

    bool EventManager::RemoveListener(EventType eventType, EventDelegate eventDelegate){
        auto findit = _listenerMap.find(eventType);
        if(findit != _listenerMap.end()){
            DelegateList & dlist = _listenerMap[eventType];
            for(auto it = dlist.begin(); it != dlist.end(); ++it){
                if(eventDelegate == (*it)){
                    dlist.erase(it);
                    return true;
                }
            }
        }
        return false;
    }


    void EventManager::EnQueue(EventPtr e){
        _eventQueue[_activeQueue].push_back(e);
    }

    /*
     *  Double buffered Queue system to eliminate potential infinite loops
     */
    void EventManager::Update(float dt){
        int queueToProcess = _activeQueue;
        _activeQueue = (_activeQueue + 1) % NUM_EVENT_QUEUES;
        _eventQueue[_activeQueue].clear();
        
        while(!_eventQueue[queueToProcess].empty()){
            EventPtr e = _eventQueue[queueToProcess].front();
            _eventQueue[queueToProcess].pop_front();

            EventType etype = e->GetEventType();
            auto it = _listenerMap.find(etype);
            if(it != _listenerMap.end()){
                // the event is listed in the event listener map. Proceed!
                
                DelegateList & dlist = _listenerMap[etype];
                for(auto listIt = dlist.begin(); listIt != dlist.end(); ++listIt){
                    // Call event listeners for each of the registered objects
                    (*listIt)(e);
                }
            }
        } 
        
    }
};
