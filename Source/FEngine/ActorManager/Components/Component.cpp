#include "Component.hpp"

namespace FEngine{

    //unsigned int Component::_nextId = 0;

    Component::Component(){
        //_id = GenNextId();
    }

    Component::~Component(){
    
    }

    const std::string & Component::GetType() const{
        return _type;
    }

    void Component::SetType(const std::string & type){
        _type = type;
    }

    void Component::SetOwner(ActorPtr & owner){
        _owner = owner;
    }

}

