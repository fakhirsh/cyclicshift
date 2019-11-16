
#pragma once

#include <EventManager/EventManager.hpp>

namespace FEngine{
    

    class Game{
        public:

            Game();
            ~Game();

            void Init();
            void Update(float dt);
            void Render(float dt);
            void Shutdown();

            void OnEvent(const EventPtr & e);

    };

};
