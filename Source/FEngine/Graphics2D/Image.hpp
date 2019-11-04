
#pragma once

#include <string>
#include <vector>
#include <memory>

namespace FEngine
{

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
        virtual bool WriteSubImage(int offsetX, int offsetY, const Image & subImage) = 0;

        virtual bool InitWithData (int width, int height, const char * data);

        void        SetName             (std::string name);
        std::string GetName             ();

        const char * GetImageData();

        int         GetWidth            ();
        int         GetHeight           ();
        int         GetDepth            ();

        unsigned int _textureID;


    protected:

        std::string	_name;

        std::string _imageType;

        int         _width;
        int         _height;
        int         _depth;
        bool        _hasAlpha;

        std::shared_ptr< std::vector<char> > _imgData;


    };

};


