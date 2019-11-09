
#pragma once

#include <string>
#include <vector>

// Swizzling is pretty awesome:
// https://stackoverflow.com/questions/14657303/convert-glmvec4-to-glmvec3
//#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <memory>

#include <Graphics2D/PNGImage.hpp>

using namespace FEngine;

namespace AtlasMaker{

    
    class System{
        public:
            
            virtual ~System();

            static std::shared_ptr<System> Get();
            
            bool LoadConfig(std::vector<char> & buffer);

            bool GenerateRectanglePacking();

            /**
                Tries to find an image of specified dimensions
                  in the image pool.
                @return Returns the actual pointer the image found.
                          returns nullptr in case of failure.
             */
            ImagePtr FindImageWithDimensions(int width, int height);

            void PrintImageList();

            System();
            
        private:
        
            std::string _inputDir;
            
            std::string _atlasName;
            std::string _atlasFormat;
            int _atlasWidth;
            int _atlasHeight;
            int _padding;
            
            std::string _packingAlgorithm;
            
            bool _debugging;
            glm::vec4 _color;
            
            std::string _localization;

            static std::shared_ptr<System> _instance;
            
            std::vector< ImagePtr > _imageList;

        private:
            
            std::string _ExecTerminalCommand(const char* cmd, std::vector<std::string> & lines);
            std::string & _ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
            std::string & _rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
            std::string & _trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
            
    };
};
