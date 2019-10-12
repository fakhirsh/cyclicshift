
#include "Game.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "../System/App.hpp"
#include <iostream>

#include "../Renderer/GL30/SimpleVertex2DProgram.hpp"

using namespace std;

namespace FEngine{

    GLuint gVertexbuffer;
    FEngine::SimpleVertex2DProgram program;

    Game::Game(){
    
    }

    Game::~Game(){
    
    }

    void Game::Init(){
        // TIP: Make sure that the alpha part is non-zero
        //   Otherwise you'll get a BLACK screen and you'll
        //   keep on wondering why :-P
    	glClearColor(0.086f, 0.063f, 0.198f, 1.0f);


        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);


        if(!program.Init()){
            std::cout << "Game::Init() --> ERROR: Couldn't initialize shader prgram" << std::endl;
            return;
        }

        static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,
        };

        glGenBuffers(1, &gVertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, gVertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    }
    
    void Game::Update(float dt){
    
    }
    
    void Game::Render(float dt){
        glClear(GL_COLOR_BUFFER_BIT);

        program.Bind();
        //program.SetMatrix(640, 480);
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
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

    }
    
    void Game::Shutdown(){
    
    }


};
