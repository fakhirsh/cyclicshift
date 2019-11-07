
#pragma once

#include <string>
#include "Image.hpp"

namespace FEngine
{
    /**
        Comcrete class for manipulating PNG file format.
     */
    class PNGImage : public Image
    {
    public:
        PNGImage();
        virtual ~PNGImage();
        
        virtual bool CreateEmpty(int width, int height, bool hasAlpha = true);
        
        /**
            Loads raw image data from file
            @param fileName Name of the image file
            @return Returns the status, success or failure.
         */
        virtual bool LoadFromFile (std::string fileName);
        
        /**
            Loads raw image data from memory stream. The file data is already in memory.
            IMPORTANT: This is NOT the decompressed raw pixel data. This is actually the 
            image file (PNG, JPEG etc) along with all its headers, compression etc.
            
            @param memoryStream Stream of image bytes as loaded in the memory.
            @return Returns the status, success or failure.
         */
        virtual bool LoadFromStream (std::istream & memoryStream);

        /**
            Save pixel data to a file
            @param fileName Name of the image file to save to
            @return Returns the status, success or failure.
         */
        virtual bool SaveToFile (std::string fileName);
        
        /**
            Save pixel data to a memory stream
            @param memoryStream memory stream representing the image to save to
            @return Returns the status, success or failure.
         */
        virtual bool SaveToStream (std::istream & memoryStream);

        /**
            Write an image (smaller or equal) to the current image.
            
            @param ofsetX X coordinate from where to start writing on the larger image.
            @param ofsetY Y coordinate from where to start writing on the larger image.
            @param subImage Sub-image to write on the current image pixel data.
            @return Returns the status, success or failure.
         */        
        virtual bool WriteSubImage(int offsetX, int offsetY, const Image & subImage);


    private:
                

    };
        
};


