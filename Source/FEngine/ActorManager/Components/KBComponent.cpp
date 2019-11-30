#include "KBComponent.hpp"

namespace FEngine{
    
    KBComponent::KBComponent(){
    
    }
    
    KBComponent::~KBComponent(){
    
    }

    bool KBComponent::Init(){
        this->SetType("keyboard");
        return false; 
    }
    
    void KBComponent::Update(float dt){
    
    }


}
