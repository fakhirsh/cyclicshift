#include "MouseComponent.hpp"

namespace FEngine{
    
    MouseComponent::MouseComponent(){
    
    }
    
    MouseComponent::~MouseComponent(){
    
    }

    bool MouseComponent::Init(){
        this->SetType("mouse");
        return false; 
    }
    
    void MouseComponent::Update(float dt){
    
    }

}

