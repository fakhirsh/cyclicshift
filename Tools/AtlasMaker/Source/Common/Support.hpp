
#pragma once

#include <string>


namespace AtlasMaker{

    struct ImageMeta{
        ImageMeta(){
            x = y = -1;
            width = height = -1;
            rotation = false;
            u = v = uW = vH = 0.0f;
        }
        std::string name;
        std::string path;
        int x, y;
        int width, height;
        bool rotation;
        float u,v,uW,vH;
    };

    /*struct Rect{*/
        //int x, y;
        
    /*};*/

};
