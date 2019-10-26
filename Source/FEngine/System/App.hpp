#pragma once

#include <string>
#include <vector>
#include <memory>

namespace FEngine
{
    class Game;

    class App;
    class IOManager;
    class Renderer;
    class SoundManager;
    class WindowManager;
    class Log;
    class EventManager;


    typedef std::shared_ptr<App> AppPtr;
    typedef std::shared_ptr<IOManager> IOManagerPtr;
    typedef std::shared_ptr<Log> LogPtr;
    typedef std::shared_ptr<Renderer> RendererPtr;
    typedef std::shared_ptr<SoundManager> SoundManagerPtr;
    typedef std::shared_ptr<EventManager> EventManagerPtr;
    typedef std::shared_ptr<WindowManager> WindowManagerPtr;
    
    
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
