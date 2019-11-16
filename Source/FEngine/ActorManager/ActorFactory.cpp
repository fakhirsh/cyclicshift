
#include "ActorFactory.hpp"
#include "Actor.hpp"

namespace FEngine{

    ActorFactoryPtr _instance = nullptr;

    ActorFactory::ActorFactory(){
        _instance = NULL;
    }

    ActorFactory::~ActorFactory(){
        if(_instance != NULL){
            delete _instance;
        }
    }

    ActorFactory * ActorFactory::Get(){
        if(_instance == NULL){
            _instance = new ActorFactory();
        }
        return _instance;
    }
    
    ActorPtr ActorFactory::CreateActor(const tinyxml2::XMLElement & actorXml){
        ActorPtr aptr = std::make_shared<Actor>();
        return aptr;
    }
}

 

