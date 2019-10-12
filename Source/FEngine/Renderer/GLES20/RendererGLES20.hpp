
#pragma once

#include "../Renderer.hpp"

namespace Fakhir
{

    class RendererGLES20 : public Renderer
    {
    public:
        RendererGLES20();
        virtual ~RendererGLES20();
        
        //virtual void BindTexture(const Texture & texture);
        virtual void UnbindTexture();
        //virtual void DeleteTexture(const Texture & texture);
        virtual unsigned int LoadTextureFromBuffer(unsigned int texWidth, unsigned int texHeight, bool hasAlpha, unsigned int * pixels );
        
        virtual void EnableBlend();
        
        virtual void ClearColor(float r, float g, float b, float a);
        virtual void Clear();
        
        virtual void SetViewPort(float x, float y, float width, float height);
    };

};
