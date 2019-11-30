#pragma once

#include <memory>
#include <map>

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

//-----------------------------------------------------    

    class Event;
    typedef std::shared_ptr<Event> EventPtr;
    typedef std::string EventType;

    class EventManager;
    typedef std::shared_ptr<EventManager> EventManagerPtr;

//-----------------------------------------------------    

    class Actor;
    typedef std::shared_ptr<Actor> ActorPtr;
    typedef std::map<int, ActorPtr> ActorMap;

    class ActorFactory;
    typedef std::shared_ptr<ActorFactory> ActorFactoryPtr;

//-----------------------------------------------------    
    
    class Component;
    typedef std::shared_ptr<Component> ComponentPtr;
   
    class TransformComponent;
    typedef std::shared_ptr<TransformComponent> TransformComponentPtr;

    class KBComponent;
    typedef std::shared_ptr<KBComponent> KBComponentPtr;

    class MouseComponent;
    typedef std::shared_ptr<MouseComponent> MouseComponentPtr;

    class ViewComponent;
    typedef std::shared_ptr<ViewComponent> ViewComponentPtr;

//-----------------------------------------------------    

    class Texture;
    typedef std::shared_ptr<Texture> TexturePtr;    

    class SpriteMetaData;
    typedef std::shared_ptr<SpriteMetaData> SpriteMetaDataPtr;

    class Sprite;
    typedef std::shared_ptr<Sprite> SpritePtr;

}
