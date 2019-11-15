
#pragma once


namespace FEngine{
    
    class Actor{
        public:

            Actor();
            ~Actor();
            
            unsigned int GetId();

            static unsigned int GenNextId();

        private:
            static unsigned int _nextId;
            unsigned int _id;
    };

}
