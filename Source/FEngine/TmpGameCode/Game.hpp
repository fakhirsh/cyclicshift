
#pragma once

namespace FEngine{
    
    class Event;

    class Game{
        public:

            Game();
            ~Game();

            void Init();
            void Update(float dt);
            void Render(float dt);
            void Shutdown();

            void OnEvent(Event e);

    };

};
