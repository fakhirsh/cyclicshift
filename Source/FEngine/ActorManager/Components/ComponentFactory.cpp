
#include "ComponentFactory.hpp"
#include "KBComponent.hpp"

namespace FEngine{

    ComponentFactory * ComponentFactory::_instance = NULL;

    ComponentFactory::ComponentFactory(){
        _instance = NULL;
    }

    ComponentFactory::~ComponentFactory(){
        if(_instance != NULL){
            delete _instance;
        }
    }

    ComponentFactory * ComponentFactory::Get(){
        if(_instance == nullptr){
            _instance = new ComponentFactory();
        }
        return _instance;
    }
    
    ComponentPtr ComponentFactory::CreateComponent(tinyxml2::XMLElement componentXml){
        ComponentPtr cptr = std::make_shared<KBComponent>();
        return cptr;
    }

}

 

