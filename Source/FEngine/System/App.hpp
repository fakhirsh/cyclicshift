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
   
            float GetElapsedTime();
            void RunGameLoop();
            
            void Shutdown();

        private:
            App();
            void Tick(float dt);
            void Input();
            void Update(float dt);
            void Render(float dt);
            
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


            Game * _testGame;
    };
    
}
