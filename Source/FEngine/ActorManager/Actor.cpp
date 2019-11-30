#include "Actor.hpp"
#include "Components/Component.hpp"
#include <System/App.hpp>
#include <Debugging/Log.hpp>

namespace FEngine{

    Actor::Actor(){ 
        _id = -1;
    }
    
    Actor::~Actor(){ }

    unsigned int Actor::GetId(){
        return _id;
    }

    std::string Actor::GetName(){
        return _name;
    }
    
    void Actor::SetName(const std::string & name){
        _name = name;
    }

    void Actor::Update(float dt){
        for(auto it = _componentMap.begin(); it != _componentMap.end(); ++it){
            ComponentPtr cp = it->second;
            cp->Update(dt);
            
            App::Get()->GetLogger()->Print(cp->GetType());
        } 
    }

    void Actor::AddComponent(ComponentPtr & component){
        //ActorPtr aptr = std::make_shared<Actor>(this);
        //component->SetOwner(aptr);
        
        std::string key = component->GetType();
        _componentMap[key] = component;
    }

    ComponentPtr Actor::GetComponent(const std::string & componentType){
        return _componentMap[componentType]; 
    }
 
}
