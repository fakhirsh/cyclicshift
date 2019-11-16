
#pragma once

#include <memory>

namespace FEngine{
   
    class TransformComponent{
        public:
            TransformComponent();
            virtual ~TransformComponent();

            virtual bool Init();
            virtual void Update(float dt);

        private:
            
    };

}
