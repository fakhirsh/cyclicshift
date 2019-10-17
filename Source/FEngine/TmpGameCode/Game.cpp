
#include "Game.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "../System/App.hpp"
#include "../Debugging/Log.hpp"
#include "../Utility/String.hpp"

#include "../Renderer/GL30/SimpleVertex2DProgram.hpp"
#include "../Graphics2D/Texture.hpp"


using namespace std;

namespace FEngine{

    GLuint gVertexbuffer;
    FEngine::SimpleVertex2DProgram program;

    Game::Game(){
    
    }

    Game::~Game(){
    
    }

    void Game::Init(){
        GLenum error = glGetError();
        if(error != GL_NO_ERROR)
        {
            App::Get()->GetLogger()->Print("Error (BEFORE glClearColor) OpenGL: (error code) " + String::ToString(error), "Game::Init");
            //return 0;
        }


        // TIP: Make sure that the alpha part is non-zero
        //   Otherwise you'll get a BLACK screen and you'll
        //   keep on wondering why :-P
    	glClearColor(0.086f, 0.063f, 0.198f, 1.0f);
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            App::Get()->GetLogger()->Print("Error (glClearColor) OpenGL: (error code) " + String::ToString(error), "Game::Init");
            //return 0;
        }



        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            App::Get()->GetLogger()->Print("Error (glGenVertexArrays) OpenGL: (error code) " + String::ToString(error), "Game::Init");
            //return 0;
        }

        glBindVertexArray(VertexArrayID);
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            App::Get()->GetLogger()->Print("Error (glBindVertexArray) OpenGL: (error code) " + String::ToString(error), "Game::Init");
            //return 0;
        }



        if(!program.Init()){
            App::Get()->GetLogger()->Print("Game::Init() --> ERROR: Couldn't initialize shader prgram");
            return;
        }
        

        float offsetX = 100.0f;
        float offsetY = 250.0f;
    
        static const GLfloat g_vertex_buffer_data[] = {
             offsetX + 0.0f, offsetY + 0.0f, 0.0f,
             offsetX + 100.0f, offsetY + 0.0f, 0.0f,
             offsetX + 100.0f, offsetY + 100.0f, 0.0f,

             offsetX + 0.0f, offsetY + 0.0f, 0.0f,
             offsetX + 100.0f, offsetY + 100.0f, 0.0f,
             offsetX + 0.0f, offsetY + 100.0f, 0.0f,

        };

        glGenBuffers(1, &gVertexbuffer);
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            App::Get()->GetLogger()->Print("Error (glGenBuffers) OpenGL: (error code) " + String::ToString(error), "Game::Init");
            //return 0;
        }

        glBindBuffer(GL_ARRAY_BUFFER, gVertexbuffer);
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            App::Get()->GetLogger()->Print("Error (glBindBuffer) OpenGL: (error code) " + String::ToString(error), "Game::Init");
            //return 0;
        }


        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            App::Get()->GetLogger()->Print("Error (glBufferData) OpenGL: (error code) " + String::ToString(error), "Game::Init");
            //return 0;
        }


        Texture t;
        if(!t.LoadFromFile("Data/Textures/player.png")){
            App::Get()->GetLogger()->Print("Texture loading failed...");
        }
        t.Bind();

        error = glGetError();
        if(error != GL_NO_ERROR)
        {
            App::Get()->GetLogger()->Print("Error (????) OpenGL: (error code) " + String::ToString(error), "Game::Init");
            //return 0;
        }

    }
    
    void Game::Update(float dt){
    
    }
    
    void Game::Render(float dt){
        glClear(GL_COLOR_BUFFER_BIT);

        program.Bind();
        program.SetMatrix(App::Get()->GetWindowWidth(), App::Get()->GetWindowHeight());
        program.SetColor(1.0, 0.0, 0.0, 1.0);
		
        // 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, gVertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

    }
    
    void Game::Shutdown(){
    
    }


};
