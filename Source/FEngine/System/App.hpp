#pragma once

#include <string>
#include <vector>

namespace FEngine
{
    class Game;

    class IOManager;
    class Renderer;
    class SoundManager;
    class WindowManager;
    class Log;
    class EventManager;

    class App
    {
        public:
            static App * Get();
            ~App();

            bool Initialize(std::string assetDirPrefix);

            bool LoadConfig(std::vector<char> & buffer);

            std::string GetClassName();
            std::string GetWindowTitle();
            int GetFps();
            int GetWindowWidth();
            int GetWindowHeight();

            void SetIOManager(IOManager * iomgr);
            IOManager * GetIOManager();
            void SetRenderer(Renderer * renderer);
            Renderer * GetRenderer();
            void SetSoundManager(SoundManager * sndmgr);
            SoundManager * GetSoundManager();
            void SetWindowManager(WindowManager * winmgr);
            WindowManager * GetWindowManager();
            void SetLogger(Log * logger);
            Log * GetLogger();

            EventManager * GetEventManager();

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

            IOManager       *   _ioManager;
            Renderer        *   _renderer;
            SoundManager    *   _soundManager;
            WindowManager   *   _windowManager;
            Log             *   _logger;
            static App      *   _app;
            EventManager    *   _eventManager;

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
