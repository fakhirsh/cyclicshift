#pragma once

#include <string>
#include <memory>
#include <tinyxml2.h>
#include "../System/Definitions.hpp"

namespace FEngine{
    
    class ActorFactory{
        public:
            virtual ~ActorFactory();
            
            static ActorFactory * Get();

            /**
             * @param actorXml Path to the XML file defining the actor
             */
            bool LoadFromFile(const std::string & path);
            ActorPtr CreateActor(const tinyxml2::XMLElement * element);

        private:
            ActorFactory();

            static ActorFactory * _instance;
    };

}
