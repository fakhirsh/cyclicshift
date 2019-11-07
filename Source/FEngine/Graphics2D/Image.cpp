
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
        _channelCount = -1;

        _imgData = nullptr;
    }


    Image::~Image ()
    {

    }

    bool Image::IsPowerOf2(int num) const{
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

    int Image::GetWidth() const
    {
        return _width;
    }

    int Image::GetHeight() const
    {
        return _height;
    }

    int Image::GetDepth() const 
    {
        return _depth;
    }


    int Image::GetChannelCount() const
    {
        return _channelCount;
    }

    void Image::SetName (std::string name)
    {
        _name = name;
    }

    const std::string & Image::GetName () const
    {
        return _name;
    }
        
    const unsigned char * Image::GetRawData() const
    {
        return _imgData->data();
    }

    PixelPtr Image::GetPixelAt(int x, int y) const 
    {
        PixelPtr pixel = std::make_shared<Pixel>();

        const unsigned char * buffer = (unsigned char *)GetRawData();
        pixel->r = buffer[y*_width*_channelCount + x*_channelCount+0];
        pixel->g = buffer[y*_width*_channelCount + x*_channelCount+1];
        pixel->b = buffer[y*_width*_channelCount + x*_channelCount+2];
        pixel->a = buffer[y*_width*_channelCount + x*_channelCount+3];
        
        return pixel;
    }

    void Image::SetPixelAt(int x, int y, const PixelPtr & pixel){
        unsigned char * buffer = (unsigned char *)GetRawData();
        buffer[y*_width*_channelCount + x*_channelCount+0] = pixel->r;
        buffer[y*_width*_channelCount + x*_channelCount+1] = pixel->g;
        buffer[y*_width*_channelCount + x*_channelCount+2] = pixel->b;
        buffer[y*_width*_channelCount + x*_channelCount+3] = pixel->a;
    }
 
};
