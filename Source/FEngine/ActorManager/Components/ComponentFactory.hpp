#pragma once

#include <string>
#include <memory>
#include <tinyxml2.h>

#include "Component.hpp"

namespace FEngine{
    
    class ComponentFactory;
    typedef std::shared_ptr<ComponentFactory> ComponentFactoryPtr;

    class ComponentFactory{
        public:

            virtual ~ComponentFactory();
            
            static ComponentFactory * Get();
            ComponentPtr CreateComponent(tinyxml2::XMLElement componentXml);

        private:
            ComponentFactory();

            static ComponentFactory * _instance;
    };

}
