
#include "Actor.hpp"

namespace FEngine{

    unsigned int Actor::_nextId = 0;

    Actor::Actor(){
        _id = GenNextId();
    }

    Actor::~Actor(){
    
    }

    unsigned int Actor::GetId(){
        return _id;
    }


    unsigned int Actor::GenNextId(){
        _nextId += 1;
        return _nextId;
    }

}

 

