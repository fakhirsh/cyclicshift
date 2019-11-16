
#pragma once

#include <map>
#include "../System/Definitions.hpp"

namespace FEngine{

    class Actor{
        public:

            Actor();
            ~Actor();
            
            unsigned int GetId();
            virtual void Update(float dt);

        private:
            unsigned int _id;

            std::map<int, ComponentPtr> _componentMap;

    };

}
