
#include "App.hpp"
#include "WindowManager.hpp"
#include <tinyxml2.h>
#include <ResourceCache/IOManager.hpp>
#include <Renderer/Renderer.hpp>
#include <Debugging/Log.hpp>
#include <Utility/String.hpp>
#include <EventManager/EventManager.hpp>
#include <EventManager/Event.hpp>

#include "../TmpGameCode/Game.hpp"

using namespace std;

namespace FEngine{

    App * App::_app = NULL;

    App::App(){
        _fps               = -1;
        _maxFps            = -1;
        _elapsed           = 0.0f;

        _sfxVolume         = -1.0f;
        _musicVolume       = -1.0f;

        _frameBufferWidth  = -1;
        _frameBufferHeight = -1;
        _windowWidth       = -1;
        _windowHeight      = -1;
        _designWidth       = -1.0f;
        _designHeight      = -1.0f;

        _allowFullScreen   = -1;
        _runFullSpeed      = -1;

        _ioManager         = nullptr;
        _renderer          = nullptr;
        _soundManager      = nullptr;
        _windowManager     = nullptr;
        _eventManager      = nullptr; 

        _testGame = new Game();
    }

    App::~App(){

    }

    App * App::Get(){
        if(_app == NULL){
            _app = new App();
        }
        return _app;
    }

    bool App::Initialize(){
        
        _eventManager = make_shared<EventManager>();

        if(_ioManager == nullptr){
            _logger->Print("IOManager MUST be set before calling Initialize()","App::Initialize");
            return false;
        }
        if(_windowManager == nullptr){
            _logger->Print("WindowManager MUST be set before calling Initialize()", "App::Initialize");
            return false;
        }

        vector<char> buffer;
        string sysConfXMLPath = _assetDirPrefix + "Config/SystemConfig.xml";
        _ioManager->GetAssetStream(sysConfXMLPath, buffer);
        if(!LoadConfig(buffer)){
            _logger->Print("Error Loading --[ " + sysConfXMLPath + " ]--", "App::Initialize");
            return false;
        }

        bool success = _windowManager->Initialize(_windowWidth, _windowHeight, _windowTitle, _className);
        if(!success){
            _logger->Print("Error Initializing _windowManager", "App::Initialize");
            return false;
        }

        auto td = TickDelegate::create<App, &App::Tick>(this);
        _windowManager->SetTickCallback(td);

        auto mpd = MousePosDelegate::create<App, &App::MousePosition>(this);
        auto mbd = MouseBtnDelegate::create<App, &App::MouseBtnPress>(this);
        auto kbd = KBDelegate::create<App, &App::KBPress>(this);
        _windowManager->SetInputCallbacks(mbd, mpd, kbd);

        _testGame->Init();

        return true;
    }


    std::string App::GetClassName(){
        return _className;
    }

    std::string App::GetWindowTitle(){
        return _windowTitle;
    }

    std::string App::GetAssetDirPrefix(){
        return _assetDirPrefix;
    }
    
    void App::SetAssetDirPrefix(std::string assetDirPrefix){
        _assetDirPrefix = assetDirPrefix;
    }


    int App::GetFps(){
        return _fps;
    }
   
    int App::GetWindowWidth(){
        return _windowWidth;
    }
    
    int App::GetWindowHeight(){
        return _windowHeight;
    }

    void App::SetIOManager(const IOManagerPtr & iomgr){
        _ioManager = iomgr;
    }

    IOManagerPtr App::GetIOManager(){
        return _ioManager;
    }

    void App::SetRenderer(const RendererPtr & renderer){
        _renderer = renderer;
    }

    RendererPtr App::GetRenderer(){
        return _renderer;
    }

    void App::SetSoundManager(const SoundManagerPtr & sndmgr){
        _soundManager = sndmgr;
    }

    SoundManagerPtr App::GetSoundManager(){
        return _soundManager;
    }

    void App::SetWindowManager(const WindowManagerPtr & winmgr){
        _windowManager = winmgr;
    }

    WindowManagerPtr App::GetWindowManager(){
        return _windowManager;
    }

    void App::SetLogger(const LogPtr & logger){
        _logger = logger;
    }

    LogPtr App::GetLogger(){
        return _logger;
    }

    EventManagerPtr App::GetEventManager(){
        return _eventManager; 
    }
    
    bool App::LoadConfig(vector<char> & buffer)
    {
        tinyxml2::XMLDocument configXML;
        tinyxml2::XMLError xmlErr;

        // The following like worked fine in linux but was giving truble in emscripten
        //xmlErr = configXML.Parse((const char *)&buffer[0]);

        std::string strBuff(buffer.begin(), buffer.end());
        xmlErr = configXML.Parse(strBuff.c_str());
        if(xmlErr != tinyxml2::XML_SUCCESS)
        {
            _logger->Print("App::LoadConfig() -- Error parsing XML from buffer (code): " + String::ToString(xmlErr));
            return false;
        }

        tinyxml2::XMLElement * root;
        tinyxml2::XMLElement * child;

        root = configXML.FirstChildElement( "SystemConfig" );

        child = root->FirstChildElement( "WindowSystem" );
        _className= child->Attribute("className");
        _windowTitle = child->Attribute("windowTitle");

        child = child->NextSiblingElement( "Graphics" );

        sscanf(child->Attribute("frameBufferWidth"), "%d", &_frameBufferWidth);
        sscanf(child->Attribute("frameBufferHeight"), "%d", &_frameBufferHeight);
        sscanf(child->Attribute("designWidth"), "%f", &_designWidth);
        sscanf(child->Attribute("designHeight"), "%f", &_designHeight);
        sscanf(child->Attribute("windowWidth"), "%d", &_windowWidth);
        sscanf(child->Attribute("windowHeight"), "%d", &_windowHeight);

        std::string fullScreen = child->Attribute("allowFullScreen");
        if(fullScreen == "false")
        {
            _allowFullScreen = false;
        }
        else
        {
            _allowFullScreen = true;
        }

        std::string fullSpeed = child->Attribute("runFullSpeed");
        if(fullSpeed == "false")
        {
            _runFullSpeed = false;
        }
        else
        {
            _runFullSpeed = true;
        }

        sscanf(child->Attribute("maxFps"), "%d", &_maxFps);

        child = child->NextSiblingElement( "Sound" );
        sscanf(child->Attribute("sfxVolume"), "%f", &_sfxVolume);
        sscanf(child->Attribute("musicVolume"), "%f", &_musicVolume);

        return true;
    }


    void App::Tick(float dt){

        static double basetime = 0.0f;
        static int frames = 0;

        _elapsed += dt;

        if ((_elapsed - basetime) > 1.0)
        {
            _fps = frames*1.0/(_elapsed - basetime);
            //std::cout << "FPS: " << _fps << std::endl;
            basetime = _elapsed;
            frames=0;
        }

        frames++;
        
        _eventManager->Update(dt);
        Input();
        Update(dt);
        Render(dt);

    }

    void App::Input(){
    
    }
    
    void App::Update(float dt){
        _testGame->Update(dt); 
    }
    
    void App::Render(float dt){
        _testGame->Render(dt);
    }

   /*
    * The actual app main loop is controlled by the OS specific window manager.
    *  We are passing the reference of "Tick" to that main loop.
    */ 
    void App::RunGameLoop(){
        _windowManager->MainLoop();
    }

    float App::GetElapsedTime(){
        return _elapsed;
    }

    void App::Shutdown(){
        _testGame->Shutdown();
    }

    void App::MousePosition(double x, double y){
        //App::Get()->GetLogger()->Print("App::Mouse = X: " + String::ToString(x) + "-- Y: " + String::ToString(y));
        
        EventPtr e = make_shared<Event>();
        e->SetEventName("Mouse Position");
        e->SetEventType("MousePosition");
        e->SetArg("x", x);
        e->SetArg("y", _windowHeight - y);
        _eventManager->EnQueue(e);
    }
    
    void App::MouseBtnPress(int button, int action, double x, double y){
        
        App::Get()->GetLogger()->Print("App::Mouse = X: " + String::ToString(x) + "-- Y: " + String::ToString(y));
    }
    
    void App::KBPress(int key, int action){
        //App::Get()->GetLogger()->Print("App::KBPressed = : " + String::ToString(key));
        EventPtr e = make_shared<Event>();
        e->SetEventName("Keyboard Press");
        e->SetEventType("KBPress");
        e->SetArg("key", key);
        e->SetArg("action", action);
        _eventManager->EnQueue(e);
    }


}
