
#include "PNGImage.hpp"
#include <png.h>
#include <iostream>

#include "../System/App.hpp"
#include "../Debugging/Log.hpp"
#include "../Utility/String.hpp"

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace FEngine
{

    PNGImage::PNGImage ()
    {
        _imageType = "png";
    }

    PNGImage::~PNGImage ()
    {

    }

    bool PNGImage::CreateEmpty(int width, int height, bool hasAlpha){
        return true;
    }

    bool PNGImage::LoadFromFile (std::string fileName){
        std::string memoryStreamString;
        std::ifstream sourceFile( fileName.c_str() );

        //Source file loaded
        if( !sourceFile )
        {
            App::Get()->GetLogger()->Print("Error: File not found: " + fileName, "PNGImage::LoadFromFile");
            return false;
        }

        //Get PNG file contents
        memoryStreamString.assign( ( std::istreambuf_iterator< char >( sourceFile ) ), std::istreambuf_iterator< char >() );

        // Convert it into a data stream
        std::istringstream memoryStream( memoryStreamString );

        bool success = LoadFromStream(memoryStream);
        if (!success)
        {
            return false;
        }

        return true;
    }

    /**
     * Please note that this function DOES NOT loads the all at once. This function
     * is called multiple times, in bursts, by the libpng library. So some kind of
     * stream handling functions are very helpful to advance the input stream read head.
     * @param   png_ptr     Pointer to png_struct initialized earlier
     * @param   destination Destination memory where the raw png data is to be copied
     * @param   bytesToRead Number of bytes that will be read in current burst/call.
     */
    void readFileCallback ( png_structp png_ptr, png_bytep destination, png_size_t bytesToRead )
    {
        png_voidp io_ptr = png_get_io_ptr( png_ptr );

        if( io_ptr == 0 )
        {
            return;
        }

        png_voidp a = png_get_io_ptr(png_ptr);
        //Cast the pointer to std::istream* and read 'bytesToRead' bytes into 'destination'
        ((std::istream*)a)->read((char*)destination, bytesToRead);
    }

    bool PNGImage::LoadFromStream (std::istream & memoryStream){

        const int PNG_SIG_BYTES = 8;
        char pngSignature[PNG_SIG_BYTES];
        memoryStream.read(pngSignature, PNG_SIG_BYTES * sizeof(char));

        if(!png_check_sig( (png_bytep)pngSignature, PNG_SIG_BYTES) )
        {
            return false;
        }

        /**
         * Create and initialize the png_struct
         * with the desired error handler
         * functions.  If you want to use the
         * default stderr and longjump method,
         * you can supply NULL for the last
         * three parameters.  We also supply the
         * the compiler header file version, so
         * that we know if the application
         * was compiled with a compatible version
         * of the library.  REQUIRED
         */
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (png_ptr == NULL)
        {
            return false;
        }

        /**
         * Allocate/initialize the memory
         * for image information.  REQUIRED. */
        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == NULL)
        {
            png_destroy_read_struct(&png_ptr, NULL, NULL);
            return false;
        }

        /**
         * Set error handling if you are
         * using the setjmp/longjmp method
         * (this is the normal method of
         * doing things with libpng).
         * REQUIRED unless you  set up
         * your own error handlers in
         * the png_create_read_struct()
         * earlier.
         */
        if (setjmp(png_jmpbuf(png_ptr))) {
            /* Free all of the memory associated
             * with the png_ptr and info_ptr */
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            return false;
        }

        /**
         * Set custom input stream READER / handler
         */
        png_set_read_fn( png_ptr, (void*)&memoryStream, readFileCallback );

        /* If we have already
         * read some of the signature */
        png_set_sig_bytes( png_ptr, 8 );

        png_read_info( png_ptr, info_ptr);

        int color_type, interlace_type;

        png_get_IHDR( png_ptr, info_ptr, (png_uint_32*)&_width, (png_uint_32*)&_height, &_depth, &color_type, &interlace_type, NULL, NULL );

        switch(color_type)
        {
            case PNG_COLOR_TYPE_RGB:
                _hasAlpha = false;
                break;
            case PNG_COLOR_TYPE_RGBA:
                _hasAlpha = true;
                break;
            default:
                return false;
                break;
        }

        png_size_t cols = png_get_rowbytes(png_ptr, info_ptr);

        png_bytepp row_pp = new png_bytep[_height];
        char * bitmapData = new char[ cols * _height ];

        for( int i = 0; i < _height; ++i )
        {
            // note that png is ordered top to
            // bottom, but OpenGL expect it bottom to top
            // so the order or swapped
            row_pp[_height - i - 1] = (png_bytep)&((char *)bitmapData)[ i * cols ];
        }

        png_read_image( png_ptr, row_pp );
        png_read_end( png_ptr, info_ptr );

        png_destroy_read_struct( &png_ptr, &info_ptr, 0 );

        delete [] row_pp;

        //RendererPtr renderer = App::Get()->GetRenderer();
        //_textureID = renderer->LoadTextureFromPixels32(_width, _height, _hasAlpha, (unsigned int *)bitmapData);

        this->InitWithData(cols, _height, bitmapData);

        delete [] bitmapData;

        return true;
    }

    bool PNGImage::SaveToFile (std::string fileName){
        return true;
    }

    bool PNGImage::SaveToStream (std::istream & memoryStream){
        return true;
    }

    bool PNGImage::WriteSubImage(int offsetX, int offsetY, const Image & subImage){
        return true;
    }

};
