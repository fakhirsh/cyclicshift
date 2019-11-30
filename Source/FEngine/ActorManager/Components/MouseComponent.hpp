#pragma once

#include "Component.hpp"

namespace FEngine{
    
    class MouseComponent : public Component{
        public:

            MouseComponent();
            virtual ~MouseComponent();

            virtual bool Init();
            virtual void Update(float dt);

        private:
       
    };

}
