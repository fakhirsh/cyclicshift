#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Definitions.hpp"

namespace FEngine
{
    class Game;
   
    class App
    {
        public:
            // Return an object reference or a smart pointer:
            // https://stackoverflow.com/questions/45127107/private-constructor-and-make-shared
            static App * Get();

            ~App();

            bool Initialize();

            bool LoadConfig(std::vector<char> & buffer);

            std::string GetClassName();
            std::string GetWindowTitle();
            std::string GetAssetDirPrefix();
            void SetAssetDirPrefix(std::string assetDirPrefix);

            int GetFps();
            int GetWindowWidth();
            int GetWindowHeight();

            static unsigned int GetNextId();

            void SetIOManager(const IOManagerPtr & iomgr);
            IOManagerPtr GetIOManager();
            void SetRenderer(const RendererPtr & renderer);
            RendererPtr GetRenderer();
            void SetSoundManager(const SoundManagerPtr & sndmgr);
            SoundManagerPtr GetSoundManager();
            void SetWindowManager(const WindowManagerPtr & winmgr);
            WindowManagerPtr GetWindowManager();
            void SetLogger(const LogPtr & logger);
            LogPtr GetLogger();

            void AddActor(ActorPtr & aptr);
            ActorPtr GetActor(int id);

            EventManagerPtr GetEventManager();

            float GetElapsedTime();
            void RunGameLoop();

            void Shutdown();


        private:
            App();
            void Tick(float dt);
            void Input();
            void Update(float dt);
            void Render(float dt);

            void MousePosition(double x, double y);
            void MouseBtnPress(int button, int action, double x, double y);
            void KBPress(int key, int action);

            std::string   _className;
            std::string   _windowTitle;
            std::string   _assetDirPrefix;

            int           _fps;
            int           _maxFps;
            double        _elapsed;

            float         _sfxVolume;
            float         _musicVolume;

            int           _frameBufferWidth;
            int           _frameBufferHeight;
            int           _windowWidth;
            int           _windowHeight;
            float         _designWidth;
            float         _designHeight;

            bool          _allowFullScreen;
            bool          _runFullSpeed;

            IOManagerPtr          _ioManager;
            RendererPtr           _renderer;
            SoundManagerPtr       _soundManager;
            WindowManagerPtr      _windowManager;
            LogPtr                _logger;
            static App  *         _app;
            EventManagerPtr       _eventManager;

            // Generates next ID for various actors/components in the game
            static unsigned int _nextId;
            ActorMap            _actorMap;

            Game * _testGame;
    };

    namespace INPUT{
        enum{
            KEY_PRESS = 1,
            KEY_RELEASE,
            MOUSE_BUTTON_LEFT,
            MOUSE_BUTTON_RIGHT,
            KB_UP,
            KB_DOWN,
            KB_LEFT,
            KB_RIGHT,
            KB_SPACE,
            KB_X
        };
    };

}
