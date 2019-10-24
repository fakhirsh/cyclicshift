

#include "GL30Renderer.hpp"

#include <GL/gl.h>

#include <iostream>
using namespace std;

namespace FEngine
{
    GL30Renderer::GL30Renderer(){
    
    }
    
    GL30Renderer::~GL30Renderer(){
    
    }
            
    void GL30Renderer::EnableBlend(){
    
    }

    void GL30Renderer::ClearColor(float r, float g, float b, float a){
        cout << "GL3Renderer::ClearColor" << endl;    
    }
    
    void GL30Renderer::Clear(){
        cout << "GL3Renderer::Clear" << endl;
    }

    void GL30Renderer::SetViewPort(float x, float y, float width, float height){
    
    }
    
    void GL30Renderer::BindTexture(unsigned int textureId){
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
    
    void GL30Renderer::UnBindTexture(){
        glBindTexture(GL_TEXTURE_2D, 0);
    }

};
