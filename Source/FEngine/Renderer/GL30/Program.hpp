//
//  Program.hpp
//  FEngine
//
//  Created by Fakhir Shaheen on 11/10/2016.
//  Copyright (c) 2016 Fakhir Shaheen. All rights reserved.
//

#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace FEngine
{

    class Program
    {
    public:
        Program();
        virtual ~Program();
        
        virtual bool    Init            ()  =   0;

        unsigned int    GetID           ();
        std::string     GetName         ();
        
        void            Bind            ();
        void            UnBind          ();
        void            UnLoad          ();
        
    protected:
        
        bool            Link        (std::string vertexShaderSource, std::string fragmentShaderSource);
        unsigned int    LoadFromFile(std::string path, unsigned int shaderType);
        unsigned int    LoadFromString(std::string shaderString, unsigned int shaderType);
        
        unsigned int    _fragmentShader;
        unsigned int    _vertexShader;
        unsigned int    _programID;
        
        std::string     _name;
    };

};


