
#pragma once

#include <string>


namespace AtlasMaker{

    struct AtlasSprite{
        AtlasSprite(){
            x = y = -1;
            width = height = -1;
            rotation = false;
        }
        std::string name;
        std::string path;
        int x, y;
        int width, height;
        bool rotation;
    };

    struct Rect{
        int x, int y;
        
    };

};
