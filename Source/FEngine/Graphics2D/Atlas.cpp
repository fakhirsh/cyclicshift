
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
        _texture->UnBind();
        //_texture->Unload();
    }

    void Atlas::Bind(){
        _texture->Bind();
    }

    void Atlas::UnBind(){
        _texture->UnBind();
    }

    SpriteMetaDataPtr Atlas::GetMetaData(std::string spriteName){
        return _metadataMap[spriteName];
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

        // The following like worked fine in linux but was giving truble 
        //   in emscripten:
        //xmlErr = configXML.Parse((const char *)&buffer[0]);
        xmlErr = configXML.Parse(mdBuffer.c_str());
        if(xmlErr != tinyxml2::XML_SUCCESS)
        {
            log->Print(string("Atlas::LoadMetaData() -- Error parsing XML from") 
                    + " buffer (code): " + String::ToString(xmlErr));
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
            std::string u1     = child->Attribute("u1");
            std::string v1     = child->Attribute("v1");
            std::string u2     = child->Attribute("u2");
            std::string v2     = child->Attribute("v2");

            SpriteMetaDataPtr smd = FENew(SpriteMetaData);
            //smd.name   = name;
            smd->x      = atoi(x.c_str());
            smd->y      = atoi(y.c_str());
            smd->width  = atoi(width.c_str());
            smd->height = atoi(height.c_str());
            smd->u1     = std::atof(u1.c_str());
            smd->v1     = std::atof(v1.c_str());
            smd->u2     = std::atof(u2.c_str());
            smd->v2     = std::atof(v2.c_str());
            if(rotation == "false"){
                smd->rotation = false;
            }else{
                smd->rotation = true;
            }

            _metadataMap[name] = smd;
 
            child = child->NextSiblingElement( "Sprite" );

        }

        return true; 
    }
 
};
