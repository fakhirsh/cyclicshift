//
//  Vertex3DProgram.cpp
//  Game
//
//  Created by Fakhir Shaheen on 28/02/2015.
//  Copyright (c) 2015 Fakhir Shaheen. All rights reserved.
//

#include "Vertex3DProgram.h"

#include "../../../../Assets/Effects/GLES20/Vertex3D.vs"
#include "../../../../Assets/Effects/GLES20/Vertex3D.fs"

namespace Fakhir
{
    
    Vertex3DProgram::Vertex3DProgram()
    {
        _positionAttrib     =   GLuint(-1);
        _texCoordAttrib     =   GLuint(-1);
        _normalAttrib       =   GLuint(-1);
        _PMVMatrixUniform   =   GLuint(-1);
    }
    
    Vertex3DProgram::~Vertex3DProgram()
    {
        
    }
    
    bool Vertex3DProgram::Init()
    {
        
        _name = "Vertex3DProgram";
        
        if (!LinkProgram(std::string(Vertex3DVS), std::string(Vertex3DFS))) {
            return false;
        }

        _positionAttrib     =	glGetAttribLocation(_programID, "a_position");
        _texCoordAttrib     =	glGetAttribLocation(_programID, "a_texCoord");
        _normalAttrib       =   glGetAttribLocation(_programID, "a_normal");
        _PMVMatrixUniform   =   glGetUniformLocation(_programID, "PMVMatrix");
        
        return true;
        
    }
    
    
    GLuint Vertex3DProgram::GetPositionAttribLocation()
    {
        return _positionAttrib;
    }
    
    GLuint Vertex3DProgram::GetTexCoordAttribLocation()
    {
        return _texCoordAttrib;
    }

    GLuint Vertex3DProgram::GetNormalAttribLocation()
    {
        return _normalAttrib;
    }
    
    GLuint Vertex3DProgram::GetPVMMatrixLoc()
    {
        return _PMVMatrixUniform;
    }
    
};


