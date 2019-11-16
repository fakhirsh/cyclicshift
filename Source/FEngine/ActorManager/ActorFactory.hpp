
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
            ActorPtr CreateActor(const tinyxml2::XMLElement & actorXml);

        private:
            ActorFactory();

            static ActorFactory * _instance;
    };

}
