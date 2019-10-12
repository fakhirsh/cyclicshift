

#pragma once


//#include "Program.hpp"



namespace FEngine
{
    class Program; 
    class SimpleVertex2DProgram : public Program
    {
    public:
        SimpleVertex2DProgram();
        ~SimpleVertex2DProgram();
        
        virtual bool    Init                        ();
        
        void            SetMatrix                   (float screenWidth, float screenHeight);
        void            SetColor                    (float r, float g, float b, float a);
        unsigned int    GetPositionAttribLocation   ();
        
    private:
        unsigned int    _positionAttrib;
        
        unsigned int    _PMVMatrixUniform;
        unsigned int    _colorUniform;
    };
    
};


