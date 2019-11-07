
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

    bool Image::IsPowerOf2(int num){
        switch(num){
            case 1:
            case 2:
            case 4:
            case 8:
            case 16:
            case 32:
            case 64:
            case 128:
            case 256:
            case 512:
            case 1024:
            case 2048:
            case 4096:
            case 8192:
                return true;
            default:
                return false;
        }
        return false;
    }

    bool Image::InitializeWithData (int width, int height, const unsigned char * data)
    {
        _imgData = std::make_shared< std::vector<unsigned char> >(data, data + width*height);
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
        
    const unsigned char * Image::GetImageData(){
        return _imgData->data();
    }
 
};
