#include "ActorFactory.hpp"
#include "Actor.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/KBComponent.hpp"
#include "Components/MouseComponent.hpp"
#include <ResourceCache/IOManager.hpp>
#include <System/App.hpp>
#include <System/Definitions.hpp>
#include <Debugging/Log.hpp>
#include <Utility/String.hpp>

using namespace std;

namespace FEngine{

    ActorFactory * ActorFactory::_instance = NULL;

    ActorFactory::ActorFactory(){ 
        _instance = NULL;
    }

    ActorFactory::~ActorFactory(){ 
        if(_instance != NULL){
            delete _instance;
        }
    }
    
    ActorFactory * ActorFactory::Get(){
        if(_instance == NULL){
            _instance = new ActorFactory();
        }
        return _instance;
    }


    bool ActorFactory::LoadFromFile(const std::string & file){
        LogPtr log = App::Get()->GetLogger();

        vector<char> buffer;
        string actorXml = App::Get()->GetAssetDirPrefix() + file;
        App::Get()->GetIOManager()->GetAssetStream(actorXml, buffer);

        tinyxml2::XMLDocument configXML;
        tinyxml2::XMLError xmlErr;

        std::string strBuff(buffer.begin(), buffer.end());
        xmlErr = configXML.Parse(strBuff.c_str());
        if(xmlErr != tinyxml2::XML_SUCCESS)
        {
            log->Print("ActorFactory::LoadFromFile() -- Error parsing XML from buffer (code): " + String::ToString(xmlErr));
            return false;
        }
        
        tinyxml2::XMLElement * root;

        root = configXML.FirstChildElement( "Actor" );

        ActorPtr actor = CreateActor(root);
        if(actor == nullptr){
            return false;
        }

        // Add the actor to App::ActorList
        
        return true;
    }


    ActorPtr ActorFactory::CreateActor(const tinyxml2::XMLElement * element){
        
        LogPtr log = App::Get()->GetLogger();
        tinyxml2::XMLElement * child;
        tinyxml2::XMLElement * component;
        
        ActorPtr actor = FENew(Actor);
        
        string actorName = element->Attribute("name");
        actor->SetName(actorName);
        actor->_id = App::Get()->GetNextId();
        App::Get()->AddActor(actor);

        child = (tinyxml2::XMLElement *)element->FirstChildElement( "Components" );

        if(child){
            std::string typeStr;            
            component = child->FirstChildElement();
        
            while(component){
                typeStr = component->Value();
                // TODO: Match for case-insensitive...
                if(typeStr == string("Transform")){
                    TransformComponentPtr tc = FENew(TransformComponent);
                    tc->x     =   atof(component->Attribute("x"));
                    tc->y     =   atof(component->Attribute("y"));
                    tc->z     =   atof(component->Attribute("y"));
                    tc->angle =   atof(component->Attribute("angle")); 
                    
                    tc->SetType(typeStr);
                    tc->SetOwner(actor);
                    ComponentPtr cp = std::dynamic_pointer_cast<Component>(tc);
                    actor->AddComponent(cp);
                }
                else if(component->Value() == string("Keyboard")){
                    KBComponentPtr tc = FENew(KBComponent);
                    
                    tc->SetType(typeStr);
                    tc->SetOwner(actor);
                    ComponentPtr cp = std::dynamic_pointer_cast<Component>(tc);
                    actor->AddComponent(cp);
                }
                else if(component->Value() == string("Mouse")){
                    MouseComponentPtr mc = FENew(MouseComponent);
                    
                    mc->SetType(typeStr);
                    mc->SetOwner(actor);
                    ComponentPtr cp = std::dynamic_pointer_cast<Component>(mc);
                    actor->AddComponent(cp);
                }
                component = component->NextSiblingElement();
            }
        }
        
        return actor;
    }

}
