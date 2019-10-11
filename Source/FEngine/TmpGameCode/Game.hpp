
#pragma once

namespace FEngine{
    
    class Game{
        public:

            Game();
            ~Game();

            void Init();
            void Update(float dt);
            void Render(float dt);
            void Shutdown();

    };

};
