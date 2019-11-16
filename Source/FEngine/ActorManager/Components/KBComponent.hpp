
#pragma once

#include "Component.hpp"

namespace FEngine{
    
    class KBComponent : public Component{
        public:

            KBComponent();
            virtual ~KBComponent();
            
            virtual bool Init();
            virtual void Update(float dt);
 
        private:

    };

}
