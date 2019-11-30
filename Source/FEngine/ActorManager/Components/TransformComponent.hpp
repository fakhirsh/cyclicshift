#pragma once

#include <memory>

#include "Component.hpp"

namespace FEngine{
   
    class TransformComponent : public Component{
        public:
            TransformComponent();
            virtual ~TransformComponent();

            virtual bool Init();
            virtual void Update(float dt);

            float x,y,z,angle;

        private:
            
    };

}
