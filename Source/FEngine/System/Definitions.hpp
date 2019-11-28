#pragma once

#include <memory>

namespace FEngine
{

    #define FENew(TYPE)  std::make_shared<TYPE>()

    class App;
    typedef std::shared_ptr<App> AppPtr;
    
    class IOManager;
    typedef std::shared_ptr<IOManager> IOManagerPtr;

    class Renderer;
    typedef std::shared_ptr<Renderer> RendererPtr;

    class SoundManager;
    typedef std::shared_ptr<SoundManager> SoundManagerPtr;

    class WindowManager;
    typedef std::shared_ptr<WindowManager> WindowManagerPtr;

    class Log;
    typedef std::shared_ptr<Log> LogPtr;

    class EventManager;
    typedef std::shared_ptr<EventManager> EventManagerPtr;

    class Actor;
    typedef std::shared_ptr<Actor> ActorPtr;

    class ActorFactory;
    typedef std::shared_ptr<ActorFactory> ActorFactoryPtr;

    class Event;
    typedef std::shared_ptr<Event> EventPtr;
    typedef std::string EventType;

    class Component;
    typedef std::shared_ptr<Component> ComponentPtr;
    
    class Texture;
    typedef std::shared_ptr<Texture> TexturePtr;    

    class SpriteMetaData;
    typedef std::shared_ptr<SpriteMetaData> SpriteMetaDataPtr;

}
