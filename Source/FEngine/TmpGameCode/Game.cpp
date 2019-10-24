
#include "Game.hpp"

#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../System/App.hpp"
#include "../Debugging/Log.hpp"
#include "../Utility/String.hpp"

#define ____EMSCRIPTEN____ 

#ifdef ____EMSCRIPTEN____
#include "../Renderer/GLES20/SimpleVertex2DProgram.hpp"
#include "../Renderer/GLES20/TexturedVertexProgram.hpp"
#else
#include "../Renderer/GL30/SimpleVertex2DProgram.hpp"
#include "../Renderer/GL30/TexturedVertexProgram.hpp"
#endif 

#include "../Renderer/Renderer.hpp"
#include "../Graphics2D/Texture.hpp"
#include "../Renderer/VertexDefinitions.hpp"

using namespace std;

namespace FEngine{

    GLuint gVertexbuffer;
    TexturedVertexProgram textureProg;
    Texture playerTexture;
    Texture enemyShipTexture;
    Texture enemyUFOTexture;

    void DrawImage(Program * program, Texture * texture, float offsetX, float offsetY);

    Game::Game(){
    
    }

    Game::~Game(){
    
    }

    void Game::Init(){
        Renderer * render = App::Get()->GetRenderer();
        render->EnableAlphaBlending();

        // TIP: Make sure that the alpha part is non-zero
        //   Otherwise you'll get a BLACK screen and you'll
        //   keep on wondering why :-P
        render->ClearColor(0.23046f, 0.472656f, 0.660156f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_BUFFER_BIT);


        if(!playerTexture.LoadFromFile("Data/Textures/player.png")){
            App::Get()->GetLogger()->Print("Texture loading failed: player.png", "Game::Init");
            return;
        }
        if(!enemyShipTexture.LoadFromFile("Data/Textures/enemyShip.png")){
            App::Get()->GetLogger()->Print("Texture loading failed: enemyShip.png", "Game::Init");
            return;
        }
        if(!enemyUFOTexture.LoadFromFile("Data/Textures/enemyUFO.png")){
            App::Get()->GetLogger()->Print("Texture loading failed: enemyUFO.png", "Game::Init");
            return;
        }


        if(!textureProg.Init()){
            App::Get()->GetLogger()->Print("ERROR: Couldn't initialize textureProgram", "Game::Init");
            return;
        }
       

/*        glGenBuffers(1, &gVertexbuffer);*/
        //glBindBuffer(GL_ARRAY_BUFFER, gVertexbuffer);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        unsigned int VertexArrayID;
        render->GenVertexArrays(1, &VertexArrayID);
        render->BindVertexArray(VertexArrayID);

    }
    
    void Game::Update(float dt){
    
    }
    
    void Game::Render(float dt){
        Renderer * render = App::Get()->GetRenderer();
        render->Clear();
        
        static float playerY = 100.0f;
        static float enemyX = 200.0f;
        static float enemyY = 250.0f;
        static float ufoY = 400.0f;
            
        DrawImage(&textureProg, &playerTexture, 100, playerY);
        DrawImage(&textureProg, &enemyShipTexture, enemyX, enemyY);
        DrawImage(&textureProg, &enemyUFOTexture, 270, ufoY);
        
        playerY += 0.4f;
        enemyX -= 0.2f;
        enemyY += 0.3f;
        ufoY -= 0.5f;
    }
    
    void Game::Shutdown(){
    
    }

    
    void DrawImage(Program * program, Texture * texture, float offsetX, float offsetY){
        
        std::vector<Vertex3PF2UVF>	_renderBatch;

        // 6 vertices per Sprite
        for(int i = 0; i < 6; i++)
        {
            Vertex3PF2UVF v;
            _renderBatch.push_back(v);
        }

        float W, H, u, v, uW, vH, angle, scaleX, scaleY, alpha, shearX, shearY;
        u       = 0.0f;
        v       = 0.0f;
        uW      = 1.0f;
        vH      = 1.0f;

        W = texture->GetWidth();
        H = texture->GetHeight();

        int i = 0;
        const int VERTS_PER_SPRITE = 6;
        
        _renderBatch[i * VERTS_PER_SPRITE].x	=	0 + offsetX;
        _renderBatch[i * VERTS_PER_SPRITE].y	=	0 + offsetY;
        _renderBatch[i * VERTS_PER_SPRITE].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE].u	=	u;
        _renderBatch[i * VERTS_PER_SPRITE].v	=	vH;
       
        _renderBatch[i * VERTS_PER_SPRITE + 1].x	=	W + offsetX;
        _renderBatch[i * VERTS_PER_SPRITE + 1].y	=	0 + offsetY;
        _renderBatch[i * VERTS_PER_SPRITE + 1].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 1].u	=	uW;
        _renderBatch[i * VERTS_PER_SPRITE + 1].v	=	vH;
       
        _renderBatch[i * VERTS_PER_SPRITE + 2].x	=	W + offsetX;
        _renderBatch[i * VERTS_PER_SPRITE + 2].y	=	H + offsetY;
        _renderBatch[i * VERTS_PER_SPRITE + 2].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 2].u	=	uW;
        _renderBatch[i * VERTS_PER_SPRITE + 2].v	=	v;
       
        _renderBatch[i * VERTS_PER_SPRITE + 3].x	=	0 + offsetX;
        _renderBatch[i * VERTS_PER_SPRITE + 3].y	=	0 + offsetY;
        _renderBatch[i * VERTS_PER_SPRITE + 3].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 3].u	=	u;
        _renderBatch[i * VERTS_PER_SPRITE + 3].v	=	vH;
       
        _renderBatch[i * VERTS_PER_SPRITE + 4].x	=	W + offsetX;
        _renderBatch[i * VERTS_PER_SPRITE + 4].y	=	H + offsetY;
        _renderBatch[i * VERTS_PER_SPRITE + 4].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 4].u	=	uW;
        _renderBatch[i * VERTS_PER_SPRITE + 4].v	=	v;
       
        _renderBatch[i * VERTS_PER_SPRITE + 5].x	=	0 + offsetX;
        _renderBatch[i * VERTS_PER_SPRITE + 5].y	=	H + offsetY;
        _renderBatch[i * VERTS_PER_SPRITE + 5].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 5].u	=	u;
        _renderBatch[i * VERTS_PER_SPRITE + 5].v	=	v;


        texture->Bind();
        
        program->Bind();
        program->SetMatrix(App::Get()->GetWindowWidth(), App::Get()->GetWindowHeight());

        int posLoc      =   textureProg.GetPositionAttribLocation();
        int uvLoc       =   textureProg.GetUVAttribLocation();

        Renderer * render = App::Get()->GetRenderer();
		
		render->EnableVertexAttribArray(posLoc);
		render->EnableVertexAttribArray(uvLoc);
       
        render->VertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (const GLvoid *)&_renderBatch[0].x);
        render->VertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat),(const GLvoid *)&_renderBatch[0].u);

		// Draw the triangle !
		render->DrawArrays(GL_TRIANGLES, 0, _renderBatch.size());

        render->DisableVertexAttribArray(uvLoc);
        render->DisableVertexAttribArray(posLoc);

        texture->UnBind();
        program->UnBind();
    }

};
