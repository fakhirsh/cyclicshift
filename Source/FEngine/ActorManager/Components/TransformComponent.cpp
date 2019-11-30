#include "TransformComponent.hpp"

namespace FEngine{

    TransformComponent::TransformComponent(){
        Init();
    }

    TransformComponent::~TransformComponent(){
    
    }
    bool TransformComponent::Init(){
        x = y = z = angle = -1.0f;
        this->SetType("transform");
        return true; 
    }
    
    void TransformComponent::Update(float dt){
    
    }


}
