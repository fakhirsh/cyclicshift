
#pragma once

#include <string>
#include <vector>
#include <memory>

namespace FEngine
{
    class Pixel;
    class Image;
    
    typedef std::shared_ptr<Pixel> PixelPtr;
    typedef std::shared_ptr<Image> ImagePtr;

    struct Pixel{
        Pixel(){r = g = b = a = 0;}
        unsigned char r,g,b,a;
    };

    /**
     *  @class Image This class serves as a base class for various image types
     *               such as PNG, JPEG, TIFF etc
     */
    class Image
    {
    public:
        Image();
        virtual ~Image();

        /**
            Creates an empty image in the Memory of given dimensions

            @param width Width of the image buffer
            @param height Height of the image buffer
            @param hasAlpha Specifies whether this image should have alpha
            transparency or not. Default is false.
            @return Returns the status, success or failure.
         */
        virtual bool CreateEmpty(int width, int height, bool hasAlpha = false) = 0;

        /**
            Loads raw image data from file
            @param fileName Name of the image file
            @return Returns the status, success or failure.
         */
        virtual bool LoadFromFile (std::string fileName) = 0;

        /**
            Loads raw image data from memory stream. The file data is already in memory.
            IMPORTANT: This is NOT the decompressed raw pixel data. This is actually the
            image file (PNG, JPEG etc) along with all its headers, compression etc.

            @param memoryStream Stream of image bytes as loaded in the memory.
            @return Returns the status, success or failure.
         */
        virtual bool LoadFromStream (std::istream & memoryStream) = 0;

        /**
            Save pixel data to a file
            @param fileName Name of the image file to save to
            @return Returns the status, success or failure.
         */
        virtual bool SaveToFile (std::string fileName) = 0;

        /**
            Save pixel data to a memory stream
            @param memoryStream memory stream representing the image to save to
            @return Returns the status, success or failure.
         */
        virtual bool SaveToStream (std::istream & memoryStream) = 0;

        /**
            Write an image (smaller or equal) to the current image.

            @param ofsetX X coordinate from where to start writing on the larger image.
            @param ofsetY Y coordinate from where to start writing on the larger image.
            @param subImage Sub-image to write on the current image pixel data.
            @return Returns the status, success or failure.
         */
        virtual bool CopyImage(int offsetX, int offsetY, const ImagePtr & imagePtr) = 0;

        virtual bool InitializeWithData (int width, int height, const unsigned char * data);

        PixelPtr    GetPixelAt(int x, int y) const;
        void        SetPixelAt(int x, int y, const PixelPtr & pixel);

        void                SetName     (std::string name);
        const std::string & GetName     () const;

        const unsigned char * GetRawData() const;

        int         GetWidth            () const;
        int         GetHeight           () const;
        int         GetDepth            () const;
        int         GetChannelCount     () const;

        bool        IsPowerOf2          (int num) const;

    protected:

        std::string	_name;

        std::string _imageType;

        int         _width;
        int         _height;
        int         _depth;
        int         _channelCount;
        bool        _hasAlpha;

        std::shared_ptr< std::vector<unsigned char> > _imgData;


    };

};


