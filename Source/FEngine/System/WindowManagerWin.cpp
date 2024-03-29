
#include "App.hpp"
#include <tinyxml2.h>
#include <iostream>
#include <ResourceCache/IOManager.hpp>

using namespace std;

namespace FEngine{

    App * App::_app = NULL;

    App::App(){
        _fps = -1;
        _maxFps = -1;

        _sfxVolume = -1.0f;
        _musicVolume = -1.0f;

        _frameBufferWidth = -1;
        _frameBufferHeight = -1;
        _windowWidth = -1;
        _windowHeight = -1;
        _designWidth = -1.0f;
        _designHeight = -1.0f;

        _allowFullScreen = -1;
        _runFullSpeed = -1;

        _ioManager = NULL;
        _renderer = NULL;
        _soundManager = NULL;
        _systemScanner = NULL;

    }

    App::~App(){

    }

    App * App::Get(){
        if(_app == NULL){
            _app = new App();
        }
        return _app;
    }

    bool App::Initialize(std::string assetDirPrefix){
        if(_ioManager == NULL){
            std::cout << "IOManager MUST be set before calling Initialize()" << endl;
            return false;
        }

        vector<char> buffer;
        string sysConfXMLPath = assetDirPrefix + "Config/SystemConfig.xml";
        _ioManager->GetAssetStream(sysConfXMLPath, buffer);
        if(!LoadConfig(buffer)){
	    	cout << "Error Loading --[ " << sysConfXMLPath << " ]--" << endl;
            return false;
        }

        cout << "Class Name: " << _className << endl;
        cout << "Window Title: " << _windowTitle << endl;
        cout << "Max FPS: " << _maxFps << endl;
        cout << "Width: " << _windowWidth << endl;
        cout << "Height: " << _windowHeight << endl;

        return true;
    }



    std::string App::GetClassName(){
        return _className;
    }

    std::string App::GetWindowTitle(){
        return _windowTitle;
    }


    void App::SetIOManager(IOManager * iomgr){
        _ioManager = iomgr;
    }

    IOManager * App::GetIOManager(){
        return _ioManager;
    }

    void App::SetRenderer(Renderer * renderer){
        _renderer = renderer;
    }

    Renderer * App::GetRenderer(){
        return _renderer;
    }

    void App::SetSoundManager(SoundManager * sndmgr){
        _soundManager = sndmgr;
    }

    SoundManager * App::GetSoundManager(){
        return _soundManager;
    }

    void App::SetSystemScanner(SystemScanner * sysscanner){
        _systemScanner = sysscanner;
    }

    SystemScanner * App::GetSystemScanner(){
        return _systemScanner;
    }

    void App::Message(){
        std::cout << "Hello from FEngine::App->Message !!!" << std::endl;
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
            cout << "App::LoadConfig() -- Error parsing XML from buffer (code): " << xmlErr << endl;
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

}
