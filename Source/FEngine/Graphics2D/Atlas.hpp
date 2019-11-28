
#pragma once

#include <string>
#include <map>
#include <memory>

#include <System/Definitions.hpp>

namespace FEngine
{

    struct SpriteMetaData{
        //std::string name;   // Do we need to store the name? 
                              //  HINT: Key is the name in sprite atlas map
        int x, y, width, height;
        float u, v, uW, vH;
        bool rotation;
    };


    /**
     *  @class Atlas A texture atlas for sprites
     */
    class Atlas
    {
        public:
            Atlas();
            virtual ~Atlas();

            bool LoadFromFile(std::string image, std::string metadata);
            
        private:
            // Function to load the metadata xml description from 
            //   a memory buffer.
            bool LoadSpriteMetaData(std::string metadataBuffer);

            //std::string _imageFileName;
            TexturePtr _texture;
            std::map<std::string, SpriteMetaDataPtr> _metadataMap;
    };
} 
