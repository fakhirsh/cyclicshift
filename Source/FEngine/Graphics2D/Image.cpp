
#include "Image.hpp"

namespace FEngine
{

    Image::Image ()
    {
        // -1 indicates invalid width/height
        _width      =   -1;
        _height     =   -1;
        _depth      =   -1;
        _hasAlpha   =   false;
        
        _imgData = nullptr;
    }


    Image::~Image ()
    {

    }

    bool Image::InitWithData (int width, int height, const char * data)
    {
        _imgData = std::make_shared< std::vector<char> >(data, data + width*height);
        return true;
    }

    int Image::GetWidth ()
    {
        return _width;
    }

    int Image::GetHeight ()
    {
        return _height;
    }

    int Image::GetDepth(){
        return _depth;
    }

    void Image::SetName (std::string name)
    {
        _name = name;
    }

    std::string Image::GetName ()
    {
        return _name;
    }
        
    const char * Image::GetImageData(){
        return _imgData->data();
    }
 
};
