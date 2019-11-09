
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
        _imgData = std::make_shared< std::vector<unsigned char> >(data, data + width * height);
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
 
    void Image::RotateCW(){

        // Create a new image buffer with changed width and height 
        //  (area of the rectangle will remain the same, obviously)
        unsigned char * bitmapData = new unsigned char[ _height * _channelCount * _width ];
        const unsigned char * img = GetRawData();

        for(int Y = 0; Y < _height; Y++){
            for(int X = 0; X < _width; X++){
                // Get old pixel value
                PixelPtr p = GetPixelAt(X, Y);
                // Calculate new pixel coordinates after rotation
                int newX = _height - Y - 1;
                int newY = X;
                // Finally compute the index for a single dimension array
                int INDEX = (newY * _height + newX) * _channelCount;
                bitmapData[INDEX + 0] = p->r;       // red
                bitmapData[INDEX + 1] = p->g;       // green
                bitmapData[INDEX + 2] = p->b;       // blue
                bitmapData[INDEX + 3] = p->a;       // alpha
            }
        }

        // The Image is rotated now. Swap width and height:
        int temp = _width;
        _width = _height;
        _height = temp;
        InitializeWithData(_width * _channelCount, _height, (const unsigned char *)bitmapData);

        delete [] bitmapData;
    }

    
    void Image::RotateCCW(){
    
    }
 
};
