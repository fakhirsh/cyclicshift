

#include "RendererGLES20.hpp"

#include "../../Graphics2D/Texture.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace Fakhir
{

    RendererGLES20::RendererGLES20()
    {

    }

    RendererGLES20::~RendererGLES20()
    {

    }

    //void RendererGLES20::BindTexture(const Texture & texture)
    //{
    //    glBindTexture(GL_TEXTURE_2D, texture.GetID());
    //}

    void RendererGLES20::UnbindTexture()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //void RendererGLES20::DeleteTexture(const Texture & texture)
    //{
    //    unsigned int textureID = texture.GetID();
    //    glDeleteTextures( 1, &textureID );
    //}
    
    void RendererGLES20::EnableBlend()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    void RendererGLES20::ClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }
    
    void RendererGLES20::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void RendererGLES20::SetViewPort(float x, float y, float width, float height)
    {
        glViewport(x, y, width, height);
    }
    
    unsigned int RendererGLES20::LoadTextureFromBuffer(unsigned int texWidth, unsigned int texHeight, bool hasAlpha, unsigned int * pixels )
    {
        //freeTexture();
        GLuint _textureID;
        
        //int _textureWidth = texWidth;
        //int _textureHeight = texHeight;
        
        glGenTextures(1, &_textureID);
        glBindTexture(GL_TEXTURE_2D, _textureID);
        GLenum error = glGetError();
        if(error != GL_NO_ERROR)
        {
            //std::cout << "Error loading texture to OpenGL" << std::endl;
            return 0;
        }
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            //std::cout << "Error loading texture to OpenGL" << std::endl;
            return 0;
        }
        
        glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, texWidth, texHeight, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, pixels);
        
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            //std::cout << "Error loading texture to OpenGL" << std::endl;
            return 0;
        }
        
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            //std::cout << "Error loading texture to OpenGL" << std::endl;
            return 0;
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            //std::cout << "Error loading texture to OpenGL" << std::endl;
            return 0;
        }
        
        return _textureID;
    }

    
};
