

#include "Renderer.hpp"

//#include <GL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

namespace FEngine
{
    Renderer::Renderer(){
    
    }
    
    Renderer::~Renderer(){
    
    }
            
    void Renderer::EnableAlphaBlending(){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::EnableDepth(){
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS); 
    }

    void Renderer::ClearColor(float r, float g, float b, float a){
    	glClearColor(r, g, b, a);
    }
    
    void Renderer::Clear(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SetViewPort(float x, float y, float width, float height){
    
    }
    
    void Renderer::BindTexture(unsigned int textureId){
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
    
    void Renderer::UnBindTexture(){
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Renderer::DeleteTextures(unsigned int size, const unsigned int * textures){
        glDeleteTextures( size, textures );
    }
    
    unsigned int Renderer::LoadTextureFromPixels32 (unsigned int texWidth, unsigned int texHeight, bool hasAlpha, unsigned int * pixels )
    {
        unsigned int textureId;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, texWidth, texHeight, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, pixels);

        /*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);*/
        /*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);*/
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        glBindTexture(GL_TEXTURE_2D, 0);

        return textureId;
    }

    void Renderer::GenVertexArrays(unsigned int size, unsigned int * arrays){
        glGenVertexArrays(size, arrays);
    }
    
    void Renderer::BindVertexArray(unsigned int arrayId){
        glBindVertexArray(arrayId);
    }

    void Renderer::EnableVertexAttribArray(int attributeLocation){
        glEnableVertexAttribArray(attributeLocation);
    }

    void Renderer::DisableVertexAttribArray(int attributeLocation){
		glDisableVertexAttribArray(attributeLocation);
    }

    void Renderer::DrawArrays(unsigned int mode, int firstIndex, int size){
        glDrawArrays(mode, firstIndex, size);
    }

    void Renderer::VertexAttribPointer(unsigned int index, int size, 
                             unsigned int type, bool normalized, 
                             unsigned int stride, const void * pointer)
    {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    }




};
