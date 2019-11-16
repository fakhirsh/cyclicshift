
#pragma once

#include <string>
#include <memory>

#include "../../System/Definitions.hpp"

namespace FEngine{
   
    class Component{
        public:

            Component();
            ~Component();
            
            const std::string & GetType();
            void SetType(const std::string & type);
            
            virtual bool Init() = 0;
            virtual void Update(float dt) = 0;

        private:
            //unsigned int _id;
            ActorPtr _parentActor;
            std::string _type;
    };

}
