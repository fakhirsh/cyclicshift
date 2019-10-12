//
//  Vertex3DProgram.h
//  Game
//
//  Created by Fakhir Shaheen on 28/02/2015.
//  Copyright (c) 2015 Fakhir Shaheen. All rights reserved.
//

#pragma once

//#include "../../Common.h"
#include "Program.h"


namespace Fakhir
{
    
    class Vertex3DProgram : public Program
    {
    public:
        Vertex3DProgram();
        ~Vertex3DProgram();
        
        virtual bool Init();
        
        GLuint GetPositionAttribLocation();
        GLuint GetTexCoordAttribLocation();
        GLuint GetNormalAttribLocation();
        GLuint GetPVMMatrixLoc();
        
    private:
        GLuint _positionAttrib;
        GLuint _texCoordAttrib;
        GLuint _normalAttrib;
        GLuint _PMVMatrixUniform;
    };
    
};
