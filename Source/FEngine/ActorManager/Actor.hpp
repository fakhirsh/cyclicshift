#pragma once

#include <map>
#include <string>
#include <System/Definitions.hpp>

namespace FEngine{

    class Actor{
        friend class ActorFactory;
        
        public:
            Actor();
            ~Actor();
            
            unsigned int GetId();
            virtual void Update(float dt);
            
            std::string GetName();
            void SetName(const std::string & name);

            void AddComponent(ComponentPtr  & component);
            ComponentPtr GetComponent(const std::string & componentType);

        private:
            unsigned int _id;
            std::string _name;
            // TODO: The key SHOULD be an integer. Strings are way too slow.
            std::map<std::string, ComponentPtr> _componentMap;

    };

}
