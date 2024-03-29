#include "SimpleVertex2DProgram.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../../System/App.hpp"
#include "../../Debugging/Log.hpp"
#include "../../Utility/String.hpp"

namespace FEngine
{

    SimpleVertex2DProgram::SimpleVertex2DProgram()
    {
        _positionAttrib     =   GLuint(-1);
        _PMVMatrixUniform   =   GLuint(-1);
        _colorUniform       =   GLuint(-1);
    }

    SimpleVertex2DProgram::~SimpleVertex2DProgram()
    {

    }

    bool SimpleVertex2DProgram::Init()
    {

        _name = "SimpleVertex2D";

        //if (!Link(std::string(SimpleVertex2DVS), std::string(SimpleVertex2DFS))) {
        if (!Link("Data/Effects/GL30/SimpleVertex2D.vs", "Data/Effects/GL30/SimpleVertex2D.fs")) {
            return false;
        }

        /**
         * Good practice:	ALWAYS get attribute location.
         * Pitfall: 		I was manually binding the locations. It Worked ONLY if
         *					done BEFORE linking the program. If the attribs are bound
         *					AFTER the program then it will NOT work on WebGL, but may
         *					work on other platforms!
         */
        _positionAttrib     =   glGetAttribLocation(_programID, "a_position");
        _PMVMatrixUniform   =   glGetUniformLocation(_programID, "PMVMatrix");
        _colorUniform       =   glGetUniformLocation(_programID, "u_color");


/*        App::Get()->GetLogger()->Print("_positionAtrib: " + String::ToString(_positionAttrib));*/
        //App::Get()->GetLogger()->Print("PMVMatrix: " + String::ToString(_PMVMatrixUniform));
        /*App::Get()->GetLogger()->Print("_colorUniform: " + String::ToString(_colorUniform));*/

        return true;

    }


    unsigned int SimpleVertex2DProgram::GetPositionAttribLocation()
    {
        return _positionAttrib;
    }

    void SimpleVertex2DProgram::SetMatrix(float screenWidth, float screenHeight)
    {
        // Get the location of the transformation matrix in the shader using its name
        //int matrixLocation = glGetUniformLocation(_programID, "PMVMatrix");

        glm::mat4 projMat = glm::ortho<GLfloat>(0.0f, screenWidth, 0.0f, screenHeight);
        //    glm::mat4 translate = glm::translate<GLfloat>(glm::mat4(1.0f), glm::vec3(width/2.0f, height/2.0f, 0.0f));
        //    glm::mat4 rotate = glm::rotate<GLfloat>(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

        //App::Get()->GetLogger()->Print(glm::to_string(projMat));
        
        glUniformMatrix4fv( _PMVMatrixUniform, 1, GL_FALSE, glm::value_ptr(projMat));

    }

    void SimpleVertex2DProgram::SetColor (float r, float g, float b, float a)
    {
        glm::vec4 color;
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;

        glUniform4f(_colorUniform, r, g, b, a);

    }

};


