
#pragma once

#include "../Renderer.hpp"

namespace FEngine
{
  
    class GL30Renderer : public Renderer
    {
    public:
        GL30Renderer();
        virtual ~GL30Renderer();
                
        virtual void EnableBlend();
        
        virtual void ClearColor(float r, float g, float b, float a);
        virtual void Clear();
        
        virtual void SetViewPort(float x, float y, float width, float height);
    
        virtual void BindTexture(unsigned int textureId);
        virtual void UnBindTexture();
    };
};
