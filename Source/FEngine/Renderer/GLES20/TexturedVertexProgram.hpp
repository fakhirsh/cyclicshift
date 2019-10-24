
#pragma once


#include "../Program.hpp"


namespace FEngine
{
    
    class TexturedVertexProgram : public Program
    {
    public:
        TexturedVertexProgram();
        ~TexturedVertexProgram();
        
        virtual bool    Init                        ();
        
        virtual void    SetMatrix                   (float screenWidth, float screenHeight);
        
        unsigned int    GetPositionAttribLocation   ();
        unsigned int    GetUVAttribLocation         ();
        
    private:
        unsigned int    _positionAttrib;
        unsigned int    _uvAttrib;
        
        unsigned int    _PMVMatrixUniform;
    };

};


