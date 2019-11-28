
#include "Atlas.hpp"
#include "Texture.hpp"
#include <tinyxml2.h>
#include <System/App.hpp>
#include <Debugging/Log.hpp>
#include <ResourceCache/IOManager.hpp>
#include <Utility/String.hpp>

#include <vector>

using namespace std;

namespace FEngine{
    
    Atlas::Atlas(){
    }
    
    Atlas::~Atlas(){
    }

    bool Atlas::LoadFromFile(std::string image, std::string metadata){
        
        string _assetDirPrefix = App::Get()->GetAssetDirPrefix();
        IOManagerPtr ioManager = App::Get()->GetIOManager();
        LogPtr log = App::Get()->GetLogger();

        _texture = FENew(Texture);
        if(!_texture->LoadFromFile(image)){
            return false;
        }

        vector<char> buffer;
        string sysConfXMLPath = _assetDirPrefix + metadata;
        ioManager->GetAssetStream(sysConfXMLPath, buffer);
        std::string strBuffer(buffer.begin(), buffer.end());
        
        if(!LoadSpriteMetaData(strBuffer)){
            return false;
        } 

        return true; 
    }

    bool Atlas::LoadSpriteMetaData(std::string mdBuffer){

        IOManagerPtr ioManager = App::Get()->GetIOManager();
        LogPtr log = App::Get()->GetLogger();

        tinyxml2::XMLDocument configXML;
        tinyxml2::XMLError xmlErr;

        // The following like worked fine in linux but was giving truble in emscripten
        //xmlErr = configXML.Parse((const char *)&buffer[0]);
        xmlErr = configXML.Parse(mdBuffer.c_str());
        if(xmlErr != tinyxml2::XML_SUCCESS)
        {
            log->Print("Atlas::LoadMetaData() -- Error parsing XML from buffer (code): " + String::ToString(xmlErr));
            return false;
        }

        tinyxml2::XMLElement * root;
        tinyxml2::XMLElement * child;

        root = configXML.FirstChildElement( "Atlas" );
        //_imageFileName= root->Attribute("imageFile");
        int spriteCount = 0;
        sscanf(root->Attribute("spriteCount"), "%d", &spriteCount);

        child = root->FirstChildElement( "Sprite" );

        while(child){
            string name        = child->Attribute("name");
            std::string x      = child->Attribute("x");
            std::string y      = child->Attribute("y");
            std::string width  = child->Attribute("width");
            std::string height = child->Attribute("height");
            std::string rotation= child->Attribute("rotation");

            SpriteMetaDataPtr smd = FENew(SpriteMetaData);
            //smd.name   = name;
            smd->x      = atoi(x.c_str());
            smd->y      = atoi(y.c_str());
            smd->width  = atoi(width.c_str());
            smd->height = atoi(height.c_str());
            smd->u      = float(smd->x) / float(_texture->GetWidth());
            smd->v      = 1.0f - float(smd->y) / float(_texture->GetHeight());
            smd->uW     = float(smd->x + smd->width) / float(_texture->GetWidth());
            smd->vH     = 1.0f - float(smd->y + smd->height) / float(_texture->GetHeight());
            if(rotation == "false"){
                smd->rotation = false;
            }else{
                smd->rotation = true;
            }

            _metadataMap[name] = smd;

            log->Print(name);
            
            child = child->NextSiblingElement( "Sprite" );

        }

        /*for(int i = 0; i < spriteCount; i++){*/
            //log->Print("Loading atlas sprites...");
            
        /*}*/

/*child = root->FirstChildElement( "WindowSystem" );*/
        //_className= child->Attribute("className");
        //_windowTitle = child->Attribute("windowTitle");

        //child = child->NextSiblingElement( "Graphics" );

        return true; 
    }
 
};
