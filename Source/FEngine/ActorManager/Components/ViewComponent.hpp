
#pragma once

#include "Component.hpp"

namespace FEngine{
    
    class ViewComponent : public Component{
        public:
            ViewComponent();
            virtual ~ViewComponent();

            virtual bool Init();
            virtual void Update(float dt);

        private:
    
    };

}
