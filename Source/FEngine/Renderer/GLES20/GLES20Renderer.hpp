
#pragma once

#include "../Renderer.hpp"

namespace Fakhir
{
    
    class GLES20Renderer : public Renderer
    {
    public:
        GLES20Renderer();
        virtual ~GLES20Renderer();
                
        virtual void EnableBlend();
        
        virtual void ClearColor(float r, float g, float b, float a);
        virtual void Clear();
        
        virtual void SetViewPort(float x, float y, float width, float height);
    };

};
