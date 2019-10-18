#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace FEngine
{

    class Program
    {
    public:
        Program();
        virtual ~Program();
        
        virtual bool Init() = 0;
        virtual void SetMatrix (float screenWidth, float screenHeight) = 0;

        GLuint GetID();
        std::string GetName();
        
        void Bind();
        void UnBind();
        void Unload();
        
    protected:
        
        bool Link(std::string vertexShaderPath, std::string fragmentShaderPath);
        GLuint LoadShaderFromFile(std::string path, GLenum shaderType);
        GLuint LoadShaderFromString(std::string shaderString, GLenum shaderType);
        
    protected:
        
        GLuint _fragmentShader;
        GLuint _vertexShader;
        GLuint _programID;
        
        std::string _name;
        
    };

};

