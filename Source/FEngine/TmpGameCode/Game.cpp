
#include "Game.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "../System/App.hpp"
#include <iostream>
using namespace std;

namespace FEngine{
   
    Game::Game(){
    
    }

    Game::~Game(){
    
    }

    void Game::Init(){
        // TIP: Make sure that the alpha part is non-zero
        //   Otherwise you'll get a BLACK screen and you'll
        //   keep on wondering why :-P
    	glClearColor(1.0f, 0.0f, 0.4f, 1.0f);
    }
    
    void Game::Update(float dt){
    
    }
    
    void Game::Render(float dt){
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void Game::Shutdown(){
    
    }


};
