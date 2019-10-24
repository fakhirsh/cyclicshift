
#pragma once


namespace FEngine
{
    /**
     * Abstract class for platform independent rendering
     */
    class Renderer
    {
    public:
        Renderer(){}
        virtual ~Renderer(){}
                
        virtual void EnableBlend() = 0;
        
        virtual void ClearColor(float r, float g, float b, float a) = 0;
        virtual void Clear() = 0;
        
        virtual void SetViewPort(float x, float y, float width, float height) = 0;

        virtual void BindTexture(unsigned int textureId) = 0;
        virtual void UnBindTexture() = 0;



    };

};
