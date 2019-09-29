//
//  SimpleVertex2D.hpp
//  FEngine
//
//  Created by Fakhir Shaheen on 11/10/2016.
//  Copyright (c) 2016 Fakhir Shaheen. All rights reserved.
//

#pragma once


#include "Program.hpp"


namespace FEngine
{
    
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


