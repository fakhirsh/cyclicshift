
#include "TexturedVertexProgram.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../../System/App.hpp"
#include "../../Debugging/Log.hpp"
#include "../../Utility/String.hpp"


namespace FEngine
{

    TexturedVertexProgram::TexturedVertexProgram()
    {
        _positionAttrib     =   GLuint(-1);
        _uvAttrib           =   GLuint(-1);
        _PMVMatrixUniform   =   GLuint(-1);
    }

    TexturedVertexProgram::~TexturedVertexProgram()
    {

    }

    bool TexturedVertexProgram::Init()
    {

        _name = "SimpleTexture";

        //if (!LinkProgram(std::string(TexturedVertexVS), std::string(TexturedVertexFS))) {
        if (!Link("Data/Effects/GLES20/TexturedVertex.vs", "Data/Effects/GLES20/TexturedVertex.fs")) {
            return false;
        }

        /**
         * Good practice:	ALWAYS get attribute location.
         * Pitfall: 		I was manually binding the locations. It Worked ONLY if
         *					done BEFORE linking the program. If the attribs are bound
         *					AFTER the program then it will NOT work on WebGL, but may
         *					work on other platforms!
         */
        _positionAttrib	=	glGetAttribLocation(_programID, "a_position");
        _uvAttrib       =   glGetAttribLocation(_programID, "a_UV");
        _PMVMatrixUniform = glGetUniformLocation(_programID, "PMVMatrix");

        return true;

    }


    unsigned int TexturedVertexProgram::GetPositionAttribLocation()
    {
        return _positionAttrib;
    }

    unsigned int TexturedVertexProgram::GetUVAttribLocation()
    {
        return _uvAttrib;
    }

    void TexturedVertexProgram::SetMatrix(float screenWidth, float screenHeight)
    {
        // Get the location of the transformation matrix in the shader using its name
        //int matrixLocation = glGetUniformLocation(_programID, "PMVMatrix");

        glm::mat4 projMat = glm::ortho<GLfloat>(0.0f, screenWidth, 0.0f, screenHeight);
        //    glm::mat4 translate = glm::translate<GLfloat>(glm::mat4(1.0f), glm::vec3(width/2.0f, height/2.0f, 0.0f));
        //    glm::mat4 rotate = glm::rotate<GLfloat>(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

        // Pass the transformationMatrix to the shader using its location
        glUniformMatrix4fv( _PMVMatrixUniform, 1, GL_FALSE, glm::value_ptr(projMat));
        //if (!TestGLError("glUniformMatrix4fv"))
        //{
        //	return false;
        //}

    }

};


