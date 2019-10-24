
#include "Program.hpp"
#include "../System/App.hpp"
#include "../Debugging/Log.hpp"
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

namespace FEngine
{

    Program::Program(void)
    {
        
        _fragmentShader = 0;
        _vertexShader = 0;
        _programID = 0;
        
    }

    Program::~Program(void)
    {
    }

    bool Program::Link(std::string vertexShaderPath, std::string fragmentShaderPath)
    {
        FEngine::App * app = FEngine::App::Get();
                    
        _vertexShader = LoadShaderFromFile(vertexShaderPath, GL_VERTEX_SHADER);
        if(_vertexShader == 0)
        {
            app->GetLogger()->Print(string("Error loading vertex shader: ") + vertexShaderPath, "Program::Link");
            return false;
        }
        
        _fragmentShader = LoadShaderFromFile(fragmentShaderPath, GL_FRAGMENT_SHADER);
        if(_fragmentShader == 0)
        {
            app->GetLogger()->Print(string("Error loading fragment shader: ") + fragmentShaderPath, "Program::Link");
            return false;
        }
        
        // Create the shader program
        _programID = glCreateProgram();
        
        // Attach the fragment and vertex shaders to it
        glAttachShader(_programID, _fragmentShader);
        glAttachShader(_programID, _vertexShader);
        
        // Link the program
        glLinkProgram(_programID);
        
        // Check if linking succeeded in the same way we checked for compilation success
        GLint isLinked;
        glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);
        if (!isLinked)
        {
            // If an error happened, first retrieve the length of the log message
            int infoLogLength, charactersWritten;
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
            
            // Allocate enough space for the message and retrieve it
            char* infoLog = new char[infoLogLength];
            glGetProgramInfoLog(_programID, infoLogLength, &charactersWritten, infoLog);
            
            app->GetLogger()->Print(string("Error linking shader: ") + infoLog);


            delete[] infoLog;
            return false;
        }
        
        return true;
    }
     
    GLuint Program::LoadShaderFromFile(std::string path, GLenum shaderType)
    {
        //Open file
        GLuint shaderID = 0;
        std::string shaderString;
        std::ifstream sourceFile( path.c_str() );
        
        //Source file loaded
        if( sourceFile )
        {
            //Get shader source
            shaderString.assign( ( std::istreambuf_iterator< char >( sourceFile ) ), std::istreambuf_iterator< char >() );
            
            shaderID = LoadShaderFromString(shaderString, shaderType);
            
        }
        else
        {
            App::Get()->GetLogger()->Print(string("ERROR: Unable to open file: ") + path.c_str(), "Program::LoadShaderFromFile");
            shaderID = 0;
        }
        
        return shaderID;
    }

    GLuint Program::LoadShaderFromString(std::string shaderString, GLenum shaderType)
    {
        GLuint shaderID = 0;
        
        //Create shader ID
        shaderID = glCreateShader( shaderType );
        
        //Set shader source
        const GLchar* shaderSource = shaderString.c_str();
        glShaderSource( shaderID, 1, (const GLchar**)&shaderSource, NULL );
        
        //Compile shader source
        glCompileShader( shaderID );
        
        //Check shader for errors
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv( shaderID, GL_COMPILE_STATUS, &shaderCompiled );
        if( shaderCompiled != GL_TRUE )
        {
            
            int infologLength = 0;
            
            int charsWritten  = 0;
            char *infoLog;
            
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH,&infologLength);
            
            std::string shaderInfoLog;
            if (infologLength > 0)
            {
                infoLog = (char *)malloc(infologLength);
                glGetShaderInfoLog(shaderID, infologLength, &charsWritten, infoLog);
                
                shaderInfoLog = infoLog;
                
                free(infoLog);
            }
            
            std::string shaderTypeStr;
            if(shaderType == GL_VERTEX_SHADER) shaderTypeStr = "Vertex Shader";
            else if(shaderType == GL_FRAGMENT_SHADER) shaderTypeStr = "Fragment Shader";
           
            Log * log = App::Get()->GetLogger();
            std::string msg = "Error compiling shader:  " + shaderTypeStr + " -- LOG:" + shaderInfoLog;
            log->Print(msg);
            log->Print("SOURCE: \n" + std::string(shaderSource));  

            glDeleteShader( shaderID );
            shaderID = 0;
        }
        
        return shaderID;
    }

    GLuint Program::GetID()
    {
        return _programID;
    }

    void Program::Bind()
    {
        glUseProgram(_programID);
    }

    void Program::UnBind()
    {
        glUseProgram(0);
    }

    void Program::Unload()
    {
        glDeleteShader(_fragmentShader);
        glDeleteShader(_vertexShader);
        glDeleteProgram(_programID);
    }

    std::string Program::GetName()
    {
        return _name;
    }

};

