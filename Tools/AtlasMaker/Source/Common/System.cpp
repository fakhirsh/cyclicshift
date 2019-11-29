
#include "System.hpp"
#include "Support.hpp"
#include <array>
#include <tinyxml2.h>
//#include <Graphics2D/Texture.hpp>
#include <System/App.hpp>
#include <Debugging/LogDefault.hpp>
#include <Utility/String.hpp>

#include <png.h>
#include <GuillotineBinPack.h>

using namespace FEngine;

namespace AtlasMaker{

    std::shared_ptr<System> System::_instance = nullptr;

    // Bunch of useful functions to "trim" the output of the ExecTerminalCommand() function
    //   i.e it removes any white space or new line characters from the end of the lines
    std::string& System::_ltrim(std::string& str, const std::string& chars)
    {
        str.erase(0, str.find_first_not_of(chars));
        return str;
    }

    std::string& System::_rtrim(std::string& str, const std::string& chars)
    {
        str.erase(str.find_last_not_of(chars) + 1);
        return str;
    }

    std::string& System::_trim(std::string& str, const std::string& chars)
    {
        return _ltrim(_rtrim(str, chars), chars);
    }

    std::string System::_ExecTerminalCommand(const char* cmd, std::vector<std::string> & lines) {
        App * app = App::Get();
        LogPtr log = App::Get()->GetLogger();

        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            //throw std::runtime_error("popen() failed!");
            log->Print("ERROR: popen() failed!", "System::_ExecTerminalCommand");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            std::string l = buffer.data();

            // The newline character and other white spaces need to be removed from
            //   the end of each line.
            result += _trim(l);

            lines.push_back(l);
        }
        return result;
    }

    System::System(){
        _atlasWidth = -1;
        _atlasHeight = -1;
        _padding = -1;

        _debugging = false;
    }

    System::~System(){

    }

    std::shared_ptr<System> System::Get(){
        if(_instance == nullptr){
            _instance = std::make_shared<System>();
        }
        return _instance;
    }

    bool System::LoadConfig(std::vector<char> & buffer){
        App * app = App::Get();
        LogPtr log = App::Get()->GetLogger();

        tinyxml2::XMLDocument configXML;
        tinyxml2::XMLError xmlErr;

        std::string strBuff(buffer.begin(), buffer.end());
        xmlErr = configXML.Parse(strBuff.c_str());
        if(xmlErr != tinyxml2::XML_SUCCESS)
        {
            log->Print("App::LoadConfig() -- Error parsing XML from buffer (code): " + String::ToString(xmlErr));
            return false;
        }

        tinyxml2::XMLElement * root;

        root = configXML.FirstChildElement( "SystemConfig" );

        tinyxml2::XMLElement * atlas = root->FirstChildElement( "Atlas" );
        _inputDir = atlas->Attribute("inputDir");
        _atlasName = atlas->Attribute("atlasName");
        _atlasFormat = atlas->Attribute("format");

        tinyxml2::XMLElement * child = atlas->FirstChildElement( "Dimensions" );
        sscanf(child->Attribute("width"), "%d", &_atlasWidth);
        sscanf(child->Attribute("height"), "%d", &_atlasHeight);

        child = child->NextSiblingElement( "Padding" );
        sscanf(child->Attribute("amount"), "%d", &_padding);

        child = child->NextSiblingElement( "Packing" );
        _packingAlgorithm = child->Attribute("algorithm");

        child = child->NextSiblingElement( "Debugging" );
        std::string isEnabled = child->Attribute("enable");
        (isEnabled == "false")?_debugging = false : _debugging = true;

        child = child->FirstChildElement( "Color" );
        sscanf(child->Attribute("r"), "%f", &_color.r);
        sscanf(child->Attribute("g"), "%f", &_color.g);
        sscanf(child->Attribute("b"), "%f", &_color.b);
        
        child = atlas->NextSiblingElement( "Localization" );
        _localization = child->Attribute("language");

        return true;
    }


    ImagePtr System::FindImageWithDimensions(int width, int height){

        for(auto it = _imageList.begin(); it != _imageList.end(); ++it){
            ImagePtr img = (*it);

            if(img->GetWidth() + _padding == width && img->GetHeight() + _padding == height){
                // Erase the image from the image list. Only images that are rotated 
                //   will be left over in the final list.
                _imageList.erase(it);
                return img;
            }
        } 
        
        return nullptr; 
    }
    

    bool System::GenerateRectanglePacking(){
        App * app = App::Get();
        LogPtr log = App::Get()->GetLogger();

        std::string command = "python3 Assets/listdir.py " + _inputDir;
    
        std::vector<std::string> lines;
        
        std::string result = _ExecTerminalCommand(command.c_str(), lines);

        if(result == ""){
            log->Print("Error: No PNG files found to begin with !");
            return false;
        }


        GuillotineBinPack gbp(_atlasWidth, _atlasHeight);

        for(auto it = lines.begin(); it != lines.end(); ++it){
            //Texture texture;
            ImagePtr imgPtr = std::make_shared<PNGImage>();
            if(imgPtr->LoadFromFile(*it)){
                imgPtr->SetName(*it);
                imgPtr->RotateCCW();

                //AtlasSprite as;

                // Delete the root name prefix from the path
                //as.path = *it;
                //as.name = (*it).erase(0, _inputDir.size());
                //as.x = 0;
                //as.y = 0;
                //as.width = img->GetWidth() + 2;
                //as.height = img->GetHeight() + 2;
                _imageList.push_back(imgPtr);
                Rect rect = gbp.Insert( imgPtr->GetWidth()+_padding, 
                                        imgPtr->GetHeight()+_padding, true, 
                                        GuillotineBinPack::RectBestAreaFit, 
                                        GuillotineBinPack::SplitMinimizeArea);
               
            }
            else{
                log->Print("Error loading: " + *it);
                return false;
            }
        }
       

        ImagePtr outPtr = std::make_shared<PNGImage>();
        outPtr->CreateEmpty(_atlasWidth, _atlasHeight); 

        App::Get()->GetLogger()->Print("Total images processed: " + String::ToString(_imageList.size()));

        std::vector<Rect> finalRects = gbp.GetUsedRectangles();
        for(auto it = finalRects.begin(); it != finalRects.end(); ++it){
            Rect rect = *it;
            //log->Print(String::ToString(rect.x) + " : " 
            //           + String::ToString(rect.y) + " --- " 
            //           + String::ToString(rect.width) + " : " 
            //           + String::ToString(rect.height));
            
            ImagePtr img = FindImageWithDimensions(rect.width, rect.height);
            if(img != nullptr){
                outPtr->CopyImage(rect.x, rect.y, img);

                ImageMetaPtr metaPtr = std::make_shared<ImageMeta>();
                metaPtr->name = img->GetName();
                metaPtr->x = rect.x;
                metaPtr->y = rect.y;
                metaPtr->width = img->GetWidth();
                metaPtr->height = img->GetHeight();
                metaPtr->rotation = false;
                
                _imageMetaInfoList.push_back(metaPtr);

            }
        }

        App::Get()->GetLogger()->Print("Images rotated: " + String::ToString(_imageList.size()));
     
        //PrintImageList();

        // Second pass for the leftover rotated rectangles / images
        for(auto it = finalRects.begin(); it != finalRects.end(); ++it){
            Rect rect = *it;
             
            ImagePtr img = FindImageWithDimensions(rect.height, rect.width);
             if(img != nullptr){
                img->RotateCW();
                outPtr->CopyImage(rect.x, rect.y, img);

                // CAREFUL: Rotateion WILL swap the width and height. This is NOT something
                //           we want to output in the XML. We need to output the original 
                //           width and height but with rotation field set to true.
                ImageMetaPtr metaPtr = std::make_shared<ImageMeta>();
                metaPtr->name = img->GetName();
                metaPtr->x = rect.x;
                metaPtr->y = rect.y;
                metaPtr->width = img->GetHeight();
                metaPtr->height = img->GetWidth();
                metaPtr->rotation = true;
                
                _imageMetaInfoList.push_back(metaPtr);

            }

        }

        outPtr->SaveToFile("./" + _atlasName + ".png");
        
        int imagesRemaining = _imageList.size();
        if(imagesRemaining > 0){
            App::Get()->GetLogger()->Print("ERROR: " + String::ToString(_imageList.size()) + " images COULD NOT be adjusted");
            App::Get()->GetLogger()->Print("ERROR: Try increasing texture atlas size...");

           PrintImageList(); 
        }
        else{
            App::Get()->GetLogger()->Print("SUCCESS: Texture Atlas created");
        }

        return true;
    }

    void System::PrintImageList(){
        for(auto it = _imageList.begin(); it != _imageList.end(); ++it){
            ImagePtr img = (*it);
            App::Get()->GetLogger()->Print(img->GetName());
        }
    }


    void System::DumpMetaXML(){

        std::string filename = _atlasName + ".xml"; 
        
        tinyxml2::XMLDocument xmlDoc;
        tinyxml2::XMLDeclaration * decl = xmlDoc.NewDeclaration();
        decl->SetValue("xml version=\"1.0\" encoding=\"UTF-8\"");

        tinyxml2::XMLElement * pRoot = xmlDoc.NewElement("Atlas");
        pRoot->SetAttribute("imageFile", filename.c_str());
        pRoot->SetAttribute("spriteCount", (int)_imageMetaInfoList.size());
        xmlDoc.InsertFirstChild(pRoot);

        
        for(auto it = _imageMetaInfoList.begin(); it != _imageMetaInfoList.end(); ++it){
            ImageMetaPtr imgPtr = (*it);
            tinyxml2::XMLElement * pElement = xmlDoc.NewElement("Sprite");
            // Delete the 'prefix' root folder from each sprite name:
            std::string filename = imgPtr->name.erase(0, _inputDir.size());
            pElement->SetAttribute("name", filename.c_str());
            pElement->SetAttribute("x", imgPtr->x);
            pElement->SetAttribute("y", imgPtr->y);
            pElement->SetAttribute("width", imgPtr->width);
            pElement->SetAttribute("height", imgPtr->height);
            pElement->SetAttribute("rotation", imgPtr->rotation);
            
            /*
             *float  u     = float(imgPtr->x) / float(_atlasWidth);
             *float  v     = 1.0f - float(imgPtr->y) / float(_atlasHeight);
             *float uW     = float(imgPtr->x + imgPtr->width) / float(_atlasWidth);
             *float vH     = 1.0f - float(imgPtr->y + imgPtr->height) / float(_atlasHeight);
             */

            float u1     = float(imgPtr->x) / float(_atlasWidth);
            float v1     = float(imgPtr->y) / float(_atlasHeight);
            float u2     = float(imgPtr->x + imgPtr->width) / float(_atlasWidth);
            float v2     = float(imgPtr->y + imgPtr->height) / float(_atlasHeight);

            pElement->SetAttribute("u1", u1);
            pElement->SetAttribute("v1", v1);
            pElement->SetAttribute("u2", u2);
            pElement->SetAttribute("v2", v2);
            
            pRoot->InsertEndChild(pElement);
        }


        tinyxml2::XMLError eResult = xmlDoc.SaveFile(filename.c_str());
    }
};
