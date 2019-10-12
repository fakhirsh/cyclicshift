#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#define STRINGIFY(A) #A

namespace Fakhir
{

    class Program
    {
    public:
        Program();
        virtual ~Program();
        
        virtual bool Init() = 0;

        GLuint GetProgramID();
        std::string GetProgramName();
        
        void Bind();
        void UnBind();
        void Unload();
        
    protected:
        
        //bool Init(std::string vertexShaderSource, std::string fragmentShaderSource);
        
        /*!*****************************************************************************************************************************************
         @Function		InitialiseShaders
         @Output		fragmentShader              Handle to a fragment shader
         @Output		vertexShader                Handle to a vertex shader
         @Output		shaderProgram               Handle to a shader program containing the fragment and vertex shader
         @Input			nativeWindow                A native window, used to display error messages
         @Return		Whether the function succeeds or not.
         @Description	Initialises shaders, buffers and other state required to begin rendering with OpenGL ES
         *******************************************************************************************************************************************/
        bool LinkProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
        GLuint LoadShaderFromFile(std::string path, GLenum shaderType);
        GLuint LoadShaderFromString(std::string shaderString, GLenum shaderType);
        
    protected:
        
        GLuint _fragmentShader;
        GLuint _vertexShader;
        GLuint _programID;
        
        std::string _name;
        
    };

};

