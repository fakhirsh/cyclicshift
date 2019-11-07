
#include "Texture.hpp"
#include <png.h>
#include <iostream>

#include "../System/App.hpp"
#include "../Debugging/Log.hpp"
#include "../Utility/String.hpp"
#include "../Renderer/Renderer.hpp"

#include "PNGImage.hpp"

#include <fstream>
#include <sstream>
#include <string>

#include <memory>

namespace FEngine
{

    Texture::Texture ()
    {
        // -1 indicates invalid width/height
        _width      =   -1;
        _height     =   -1;
        _depth      =   -1;
        _textureID  =   0;
        _hasAlpha   =   false;
    }


    Texture::~Texture ()
    {

    }

    bool Texture::Init ()
    {
        return true;
    }

    int Texture::GetWidth ()
    {
        return _width;
    }

    int Texture::GetHeight ()
    {
        return _height;
    }

    unsigned int Texture::GetID ()
    {
        return _textureID;
    }

    void Texture::SetName (std::string name)
    {
        _name = name;
    }

    std::string Texture::GetName ()
    {
        return _name;
    }

    void Texture::Bind ()
    {
        RendererPtr renderer = App::Get()->GetRenderer();
        renderer->BindTexture(_textureID);
    }

    void Texture::UnBind ()
    {
        RendererPtr renderer = App::Get()->GetRenderer();
        renderer->UnBindTexture();
    }

    bool Texture::LoadFromFile (std::string fileName)
    {
        std::shared_ptr<Image> imgPtr = std::make_shared<PNGImage>();

        if(!imgPtr->LoadFromFile(fileName)){
            App::Get()->GetLogger()->Print("Error: Loading from File: " + fileName, "Texture::LoadFromFile");
            return false;
        }

        _width  = imgPtr->GetWidth();
        _height = imgPtr->GetHeight();
        _depth  = imgPtr->GetDepth();
        _hasAlpha = true;

        RendererPtr renderer = App::Get()->GetRenderer();
        _textureID = renderer->LoadTextureFromPixels32(_width, _height, _hasAlpha, (unsigned int *)imgPtr->GetRawData());

        return true;
    }

    bool Texture::SetTexture (unsigned int textureID, int width, int height, bool hasAlpla)
    {
        _textureID  =   textureID;
        _width      =   width;
        _height     =   height;
        _hasAlpha   =   hasAlpla;

        return true;
    }

    void Texture::Unload ()
    {
        //Delete texture
        if( _textureID != 0 )
        {
            RendererPtr renderer = App::Get()->GetRenderer();
            renderer->DeleteTextures(1, &_textureID);
        }
    }




//-----------------------------------------------------------------------------------------

    /**
     * Sample function showing how to generate and load textures from memory
     */
/*
 *    bool LoadTexturesFromMem ()
 *    {
 *        GLuint _uiTexture;
 *
 *        glGenTextures(1, &_uiTexture);
 *
 *        // Binds this texture handle so we can load the data into it
 *        glBindTexture(GL_TEXTURE_2D, _uiTexture);
 *
 *        const int TEX_SIZE = 128;
 *        // Creates the data as a 32bits integer array (8bits per component)
 *        GLuint* pTexData = new GLuint[TEX_SIZE*TEX_SIZE];
 *        for (int i=0; i<TEX_SIZE; i++)
 *            for (int j=0; j<TEX_SIZE; j++)
 *            {
 *                // Fills the data with a fancy pattern
 *                GLuint col = (255<<24) + ((255-j*2)<<16) + ((255-i)<<8) + (255-i*2);
 *                if ( ((i*j)/8) % 2 ) col = (GLuint) (255<<24) + (255<<16) + (0<<8) + (255);
 *                pTexData[j*TEX_SIZE+i] = col;
 *            }
 *
 *        //[>
 *         //glTexImage2D loads the texture data into the texture object.
 *         //void glTexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
 *         //GLint border, GLenum format, GLenum type, const GLvoid *pixels );
 *         //target must be GL_TEXTURE_2D.
 *         //level specify the mipmap level we want to upload.
 *         //internalformat and format must be the same. Here we use GL_RGBA for 4 component colors (r,g,b,a).
 *         //We could use GL_RGB, GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA to use different color component combinations.
 *         //width, height specify the size of the texture. Both of the dimensions must be power of 2.
 *         //border must be 0.
 *         //type specify the format of the data. We use GL_UNSIGNED_BYTE to describe a color component as an unsigned byte.
 *         //So a pixel is described by a 32bits integer.
 *         //We could also use GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, and GL_UNSIGNED_SHORT_5_5_5_1
 *         //to specify the size of all 3 (or 4) color components. If we used any of these 3 constants,
 *         //a pixel would then be described by a 16bits integer.
 *         
 *        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, pTexData);
 *
 *        [>
 *         //glTexParameterf is used to set the texture parameters
 *         //void glTexParameterf(GLenum target, GLenum pname, GLfloat param);
 *         //target must be GL_TEXTURE_2D.
 *         //pname is the parameter name we want to modify.
 *         //If pname is GL_TEXTURE_MIN_FILTER, param is used to set the way the texture is rendered when made smaller.
 *         //We can tell OpenGL to interpolate between the pixels in a mipmap level but also between different mipmap levels.
 *         //We are not using mipmap interpolation here because we didn't defined the mipmap levels of our texture.
 *
 *         //If pname is GL_TEXTURE_MAG_FILTER, param is used to set the way the texture is rendered when made bigger.
 *         //Here we can only tell OpenGL to interpolate between the pixels of the first mipmap level.
 *
 *         //if pname is GL_TEXTURE_WRAP_S or GL_TEXTURE_WRAP_T, then param sets the way a texture tiles in both directions.
 *         //The default if GL_REPEAT to wrap the texture (repeat it). We could also set it to GL_CLAMP or GL_CLAMP_TO_EDGE
 *         //to clamp the texture.
 *
 *         //On OpenGL ES 1.1 and 2.0, if pname is GL_GENERATE_MIPMAP, param tells OpenGL to create mipmap levels automatically.
 *         
 *        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
 *        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
 *
 *        // Deletes the texture data, it's now in OpenGL memory
 *        delete [] pTexData;
 *
 *        glBindTexture(GL_TEXTURE_2D, 0);
 *
 *        return true;
 *
 *    }
 */

};
