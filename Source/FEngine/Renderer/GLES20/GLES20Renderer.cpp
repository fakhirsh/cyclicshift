

#include "GLES20Renderer.hpp"

#include <iostream>
using namespace std;

namespace Fakhir
{
    GLES20Renderer::GLES20Renderer(){
    
    }
    
    GLES20Renderer::~GLES20Renderer(){
    
    }
            
    void GLES20Renderer::EnableBlend(){
    
    }

    void GLES20Renderer::ClearColor(float r, float g, float b, float a){
        cout << "GLES20Renderer::ClearColor" << endl;    
    }
    
    void GLES20Renderer::Clear(){
        cout << "GLES20Renderer::Clear" << endl;
    }

    void GLES20Renderer::SetViewPort(float x, float y, float width, float height){
    
    }

};
