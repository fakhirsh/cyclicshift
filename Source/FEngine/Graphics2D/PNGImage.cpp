
#include "PNGImage.hpp"
#include <png.h>
#include <iostream>

#include "../System/App.hpp"
#include "../Debugging/Log.hpp"
#include "../Utility/String.hpp"

#include <fstream>
#include <sstream>
#include <string>


#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


using namespace std;

namespace FEngine
{


    inline void setRGB(png_byte *ptr, float val)
    {
        int v = (int)(val * 767);
        if (v < 0) v = 0;
        if (v > 767) v = 767;
        int offset = v % 256;

        if (v<256) {
            ptr[0] = 0; ptr[1] = 0; ptr[2] = offset;
        }
        else if (v<512) {
            ptr[0] = 0; ptr[1] = offset; ptr[2] = 255-offset;
        }
        else {
            ptr[0] = offset; ptr[1] = 255-offset; ptr[2] = 0;
        }
    }

    int writeImage(char* filename, int width, int height, float *buffer, char* title)
    {
        int code = 0;
        FILE *fp = NULL;
        png_structp png_ptr = NULL;
        png_infop info_ptr = NULL;
        png_bytep row = NULL;
        
        // Open file for writing (binary mode)
        fp = fopen(filename, "wb");
        if (fp == NULL) {
            fprintf(stderr, "Could not open file %s for writing\n", filename);
            code = 1;
            goto finalise;
        }

        // Initialize write structure
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (png_ptr == NULL) {
            fprintf(stderr, "Could not allocate write struct\n");
            code = 1;
            goto finalise;
        }

        // Initialize info structure
        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == NULL) {
            fprintf(stderr, "Could not allocate info struct\n");
            code = 1;
            goto finalise;
        }

        // Setup Exception handling
        if (setjmp(png_jmpbuf(png_ptr))) {
            fprintf(stderr, "Error during png creation\n");
            code = 1;
            goto finalise;
        }

        png_init_io(png_ptr, fp);

        // Write header (8 bit colour depth)
        png_set_IHDR(png_ptr, info_ptr, width, height,
                8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        // Set title
        if (title != NULL) {
            png_text title_text;
            title_text.compression = PNG_TEXT_COMPRESSION_NONE;
            title_text.key = "Title";
            title_text.text = title;
            png_set_text(png_ptr, info_ptr, &title_text, 1);
        }

        png_write_info(png_ptr, info_ptr);

        // Allocate memory for one row (3 bytes per pixel - RGB)
        row = (png_bytep) malloc(4 * width * sizeof(png_byte));

        // Write image data
        int x, y;
        for (y=0 ; y<height ; y++) {
            for (x=0 ; x<width ; x++) {
                //setRGB(&(row[x*3]), buffer[y*width + x]);
                row[x*4+0] = 0;
                row[x*4+1] = 255;
                row[x*4+2] = 0;
                row[x*4+3] = 100;
            }
            png_write_row(png_ptr, row);
        }

        // End write
        png_write_end(png_ptr, NULL);

        finalise:
        if (fp != NULL) fclose(fp);
        if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
        if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        if (row != NULL) free(row);

        return code;
    }

    float * createSolidColor(int width, int height){
        
        float *buffer = (float *) malloc(width * height * sizeof(float));
        if (buffer == NULL) {
            fprintf(stderr, "Could not create image buffer\n");
            return NULL;
        }

        int xPos, yPos;

        for (yPos=0 ; yPos<height ; yPos++)
        {
            for (xPos=0 ; xPos<width ; xPos++)
            {
                buffer[yPos * width + xPos] = 0;
            }
        }
        return buffer;
    }



    PNGImage::PNGImage ()
    {
        _imageType = "png";
    }

    PNGImage::~PNGImage ()
    {

    }

/*
 *    bool PNGImage::CreateEmpty(int width, int height, bool hasAlpha){
 *
 *        // Specify an output image size
 *        //int width = 500;
 *        //int height = 300;
 *
 *        // Create a test image - in this case a Mandelbrot Set fractal
 *        // The output is a 1D array of floats, length: width * height
 *        printf("Creating Image\n");
 *        //float *buffer = createMandelbrotImage(width, height, -0.802, -0.177, 0.011, 110);
 *        float *buffer = createSolidColor(width, height);
 *        if (buffer == NULL) {
 *            return false;
 *        }
 *
 *        // Save the image to a PNG file
 *        // The 'title' string is stored as part of the PNG file
 *        printf("Saving PNG\n");
 *        int result = writeImage("output.png", width, height, buffer, "This is my test image");
 *
 *        // Free up the memorty used to store the image
 *        free(buffer);
 *
 *
 *
 *        return true;
 *    }
 *
 */

    bool PNGImage::CreateEmpty(int width, int height, bool hasAlpha){

        _width = width;
        _height = height;
        _hasAlpha = hasAlpha; 
       
        int numChannels = 4;

        unsigned char * bitmapData = new unsigned char[ _width * numChannels * _height ];

        for(int R = 0; R < _height; R++){
            for(int C = 0; C < _width; C++){
                bitmapData[R*_width*numChannels + C*numChannels + 0] = (unsigned char)255;   // red
                bitmapData[R*_width*numChannels + C*numChannels + 1] = (unsigned char)0; // green
                bitmapData[R*_width*numChannels + C*numChannels + 2] = (unsigned char)0;   // blue
                bitmapData[R*_width*numChannels + C*numChannels + 3] = (unsigned char)255;  // alpha
            }
        }
        
        this->InitWithData(_width * numChannels, _height, (const char *)bitmapData);

        delete [] bitmapData;

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
