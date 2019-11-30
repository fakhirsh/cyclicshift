
#include "Game.hpp"

#include <vector>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>

#include <System/App.hpp>
#include <Debugging/Log.hpp>
#include <Utility/String.hpp>
#include <Utility/Math.hpp>
#include <ActorManager/ActorFactory.hpp>

#include <EventManager/Event.hpp>

//#define ____EMSCRIPTEN____ 

#ifdef ____EMSCRIPTEN____
#include <Renderer/GLES20/SimpleVertex2DProgram.hpp>
#include <Renderer/GLES20/TexturedVertexProgram.hpp>
#else
#include <Renderer/GL30/SimpleVertex2DProgram.hpp>
#include <Renderer/GL30/TexturedVertexProgram.hpp>
#endif 

#include <Renderer/Renderer.hpp>
#include <Graphics2D/Texture.hpp>
#include <Graphics2D/PNGImage.hpp>
#include <Renderer/VertexDefinitions.hpp>
#include <Graphics2D/Atlas.hpp>


using namespace std;

namespace FEngine{

    GLuint gVertexbuffer;
    TexturedVertexProgram textureProg;
    Texture playerTexture;
    Texture enemyShipTexture;
    Texture enemyUFOTexture;

    Atlas atlas;

    void DrawImage(Program * program, Texture * texture, float offsetX, float offsetY);
    void RenderSprite(Program * program, string spriteName, float offsetX, float offsetY);

    float playerX = 100.0f;
    float playerY = 100.0f;
    float enemyX = 200.0f;
    float enemyY = 250.0f;
    float enemyVX = 0.0f;
    float enemyVY = 0.0f;
    const float ENEMY_VELOCITY = 300;
    float UFO_VELOCITY = -0.4;
    float ufoY = 400.0f;
    float g_angle = 0.0f;
    float scale = 1.0f;

    Game::Game(){
    }

    Game::~Game(){
    }

    void Game::Init(){
        RendererPtr render = App::Get()->GetRenderer();

        render->EnableAlphaBlending();
        //render->EnableDepth();
        
        // TIP: Make sure that the alpha part is non-zero
        //   Otherwise you'll get a BLACK screen and you'll
        //   keep on wondering why :-P
        render->ClearColor(0.23046f, 0.472656f, 0.660156f, 1.0f);
        
        bool result = false;
        result = ActorFactory::Get()->LoadFromFile("Actors/player.xml");
        result = ActorFactory::Get()->LoadFromFile("Actors/enemy.xml");

        if(!atlas.LoadFromFile("Textures/zombie.png", "Textures/zombie.xml")){
        //if(!atlas.LoadFromFile("Textures/game.png", "Textures/game.xml")){
            return;
        }

/*        if(!playerTexture.LoadFromFile("Textures/player.png")){*/
            //App::Get()->GetLogger()->Print("Texture loading failed: player.png", "Game::Init");
            //return;
        //}
        //if(!enemyShipTexture.LoadFromFile("Textures/enemyShip.png")){
            //App::Get()->GetLogger()->Print("Texture loading failed: enemyShip.png", "Game::Init");
            //return;
        //}
        //if(!enemyUFOTexture.LoadFromFile("Textures/enemyUFO.png")){
            //App::Get()->GetLogger()->Print("Texture loading failed: enemyUFO.png", "Game::Init");
            //return;
        /*}*/

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

        EventManagerPtr emgr = App::Get()->GetEventManager();

        auto mpd = EventDelegate::create<Game, &Game::OnEvent>(this);
        emgr->AddListener("MousePosition", mpd);
        emgr->AddListener("KBPress", mpd);

    }
    
    void Game::Update(float dt){
        g_angle += 0.1;
    }
    
    void Game::OnEvent(const EventPtr & e){
        if(e->GetEventType() == "MousePosition"){
            double x = e->GetArg("x");
            double y = e->GetArg("y");
            //App::Get()->GetLogger()->Print("Game::OnEvent = X: " + String::ToString(x) + "-- Y: " + String::ToString(y));
            playerX = x;
            playerY = y;
        }
        else if(e->GetEventType() == "KBPress"){
            //enemyVX =enemyVY = 0.0f;

            int key = e->GetArg("key");
            int action = e->GetArg("action");
    

            if(action == INPUT::KEY_PRESS){
                if(key == INPUT::KB_UP){
                    enemyVY = ENEMY_VELOCITY;
                }if(key == INPUT::KB_DOWN){
                    enemyVY = -ENEMY_VELOCITY;
                }if(key == INPUT::KB_LEFT){
                    enemyVX = -ENEMY_VELOCITY;
                }if(key == INPUT::KB_RIGHT){
                    enemyVX = ENEMY_VELOCITY;
                }
            }
            if(action == INPUT::KEY_RELEASE){
                if(key == INPUT::KB_UP){
                    enemyVY = 0.0f;
                }if(key == INPUT::KB_DOWN){
                    enemyVY = 0.0f;
                }if(key == INPUT::KB_LEFT){
                    enemyVX = 0.0f;
                }if(key == INPUT::KB_RIGHT){
                    enemyVX = 0.0f;
                }
            }
        }

    }
    
    
    void Game::Render(float dt){
        RendererPtr render = App::Get()->GetRenderer();
        render->Clear();
        
        /*DrawImage(&textureProg, &playerTexture, playerX - playerTexture.GetWidth()/2, playerY - playerTexture.GetHeight()/2);*/
        //DrawImage(&textureProg, &enemyShipTexture, enemyX, enemyY);
        /*DrawImage(&textureProg, &enemyUFOTexture, 270, ufoY);*/
             /* RenderSprite(&textureProg, "player.png", playerX - playerTexture.GetWidth()/2, playerY - playerTexture.GetHeight()/2);*/
        //RenderSprite(&textureProg, "enemyShip.png", enemyX, enemyY);
        /*RenderSprite(&textureProg, "enemyUFO.png", 270, ufoY);*/
        RenderSprite(&textureProg, "player.png", playerX - playerTexture.GetWidth()/2, playerY - playerTexture.GetHeight()/2);
        RenderSprite(&textureProg, "enemyShip.png", enemyX, enemyY);
        RenderSprite(&textureProg, "enemyUFO.png", 270, ufoY);
        RenderSprite(&textureProg, "Kings and Pigs/Sprites/02-King Pig/Fall (38x28).png", 70, ufoY);
        RenderSprite(&textureProg, "loadinglbl.png", App::Get()->GetWindowWidth()/2.0f, App::Get()->GetWindowHeight()/2.0f);
        RenderSprite(&textureProg, "lbl_getReady.png", App::Get()->GetWindowWidth()/2.0f, 500.0f);
        RenderSprite(&textureProg, "PixelArt/Enemies/FatBird/Fall (40x48).png", App::Get()->GetWindowWidth()/2.0f, 150.0f);


        enemyX += enemyVX * dt;
        enemyY += enemyVY * dt;
        
        //ufoY += 0.400;
        /*
         *if(ufoY <= 0){
         *    UFO_VELOCITY = 0.4;
         *}
         *else if(ufoY > App::Get()->GetWindowHeight()){
         *    UFO_VELOCITY = -0.4;
         *}
         */

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

        float W, H, u1, v, uW, vH, angle, scaleX, scaleY, alpha, shearX, shearY;
        u1      = 0.0f;
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
        _renderBatch[i * VERTS_PER_SPRITE].u	=	u1;
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
        _renderBatch[i * VERTS_PER_SPRITE + 3].u	=	u1;
        _renderBatch[i * VERTS_PER_SPRITE + 3].v	=	vH;
       
        _renderBatch[i * VERTS_PER_SPRITE + 4].x	=	W + offsetX;
        _renderBatch[i * VERTS_PER_SPRITE + 4].y	=	H + offsetY;
        _renderBatch[i * VERTS_PER_SPRITE + 4].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 4].u	=	uW;
        _renderBatch[i * VERTS_PER_SPRITE + 4].v	=	v;
       
        _renderBatch[i * VERTS_PER_SPRITE + 5].x	=	0 + offsetX;
        _renderBatch[i * VERTS_PER_SPRITE + 5].y	=	H + offsetY;
        _renderBatch[i * VERTS_PER_SPRITE + 5].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 5].u	=	u1;
        _renderBatch[i * VERTS_PER_SPRITE + 5].v	=	v;


        texture->Bind();
        
        program->Bind();
        program->SetMatrix(App::Get()->GetWindowWidth(), App::Get()->GetWindowHeight());

        int posLoc      =   textureProg.GetPositionAttribLocation();
        int uvLoc       =   textureProg.GetUVAttribLocation();

        RendererPtr render = App::Get()->GetRenderer();
		
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


    void RenderSprite(Program * program, string spriteName, float offsetX, float offsetY){
        
        std::vector<Vertex3PF2UVF>	_renderBatch;

        // 6 vertices per Sprite
        for(int i = 0; i < 6; i++){
            Vertex3PF2UVF v;
            _renderBatch.push_back(v);
        }
        
        SpriteMetaDataPtr smd = atlas.GetMetaData(spriteName);
        
        float W, H, u1, v1, u2, v2, angle, scaleX, scaleY, alpha, shearX, shearY;
        u1      = smd->u1;
        v1      = smd->v1;
        u2      = smd->u2;
        v2      = smd->v2;

        /*LogPtr lg = App::Get()->GetLogger();*/
        /*lg->Print(spriteName + " -- u: "+String::ToString(u1)+"  v: "+String::ToString(v1)+"  u2: "+String::ToString(u2)+"  v2: "+String::ToString(v2));*/

        W = smd->width;
        H = smd->height;

        angle = 0.0f;
        if(smd->rotation){
            angle = 90.0f;
        }

        glm::mat4 translate = glm::translate<GLfloat>(glm::mat4(1.0f), glm::vec3(offsetX, offsetY, 0.0f));
        glm::mat4 rotate    = glm::rotate   <GLfloat>(glm::mat4(1.0f),
                                                      Math::DegToRad(g_angle + angle),
                                                      glm::vec3(0.0f, 0.0f, 1.0f));
        
        glm::mat4 scale     = glm::scale    <GLfloat>(glm::mat4(1.0f), glm::vec3(1.0f,
                                                                                 1.0f,
                                                                                 1.0f));
        
        glm::mat4 translateAnchor = glm::translate<GLfloat>(glm::mat4(1.0f), glm::vec3(-W/2, -H/2.0f, 0.0f));
        //glm::mat4 shearX    = glm::mat4(1.0f);
        //shearX[1][0] = _sceneNodeProperties2D->shearX;
        
        
        glm::mat4 localMat = translate * rotate * scale * translateAnchor;
        
        
        int i = 0;
        const int VERTS_PER_SPRITE = 6;
       
        glm::vec4 vec = localMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        _renderBatch[i * VERTS_PER_SPRITE].x	=	vec.x;
        _renderBatch[i * VERTS_PER_SPRITE].y	=	vec.y;
        _renderBatch[i * VERTS_PER_SPRITE].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE].u	=	u1;
        _renderBatch[i * VERTS_PER_SPRITE].v	=	v2;

        vec = localMat * glm::vec4(W, 0.0f, 0.0f, 1.0f);
        _renderBatch[i * VERTS_PER_SPRITE + 1].x	=	vec.x;
        _renderBatch[i * VERTS_PER_SPRITE + 1].y	=	vec.y;
        _renderBatch[i * VERTS_PER_SPRITE + 1].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 1].u	=	u2;
        _renderBatch[i * VERTS_PER_SPRITE + 1].v	=	v2;
       
        vec = localMat * glm::vec4(W, H, 0.0f, 1.0f);
        _renderBatch[i * VERTS_PER_SPRITE + 2].x	=	vec.x;
        _renderBatch[i * VERTS_PER_SPRITE + 2].y	=	vec.y;
        _renderBatch[i * VERTS_PER_SPRITE + 2].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 2].u	=	u2;
        _renderBatch[i * VERTS_PER_SPRITE + 2].v	=	v1;
       
        vec = localMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        _renderBatch[i * VERTS_PER_SPRITE + 3].x	=	vec.x;
        _renderBatch[i * VERTS_PER_SPRITE + 3].y	=	vec.y;
        _renderBatch[i * VERTS_PER_SPRITE + 3].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 3].u	=	u1;
        _renderBatch[i * VERTS_PER_SPRITE + 3].v	=	v2;
       
        vec = localMat * glm::vec4(W, H, 0.0f, 1.0f);
        _renderBatch[i * VERTS_PER_SPRITE + 4].x	=	vec.x;
        _renderBatch[i * VERTS_PER_SPRITE + 4].y	=	vec.y;
        _renderBatch[i * VERTS_PER_SPRITE + 4].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 4].u	=	u2;
        _renderBatch[i * VERTS_PER_SPRITE + 4].v	=	v1;
       
        vec = localMat * glm::vec4(0.0f, H, 0.0f, 1.0f);
        _renderBatch[i * VERTS_PER_SPRITE + 5].x	=	vec.x;
        _renderBatch[i * VERTS_PER_SPRITE + 5].y	=	vec.y;
        _renderBatch[i * VERTS_PER_SPRITE + 5].z	=	0;
        _renderBatch[i * VERTS_PER_SPRITE + 5].u	=	u1;
        _renderBatch[i * VERTS_PER_SPRITE + 5].v	=	v1;


        atlas.Bind();        
        
        program->Bind();
        program->SetMatrix(App::Get()->GetWindowWidth(), App::Get()->GetWindowHeight());

        int posLoc      =   textureProg.GetPositionAttribLocation();
        int uvLoc       =   textureProg.GetUVAttribLocation();

        RendererPtr render = App::Get()->GetRenderer();
		
		render->EnableVertexAttribArray(posLoc);
		render->EnableVertexAttribArray(uvLoc);
       
        render->VertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (const GLvoid *)&_renderBatch[0].x);
        render->VertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat),(const GLvoid *)&_renderBatch[0].u);

		// Draw the triangle !
		render->DrawArrays(GL_TRIANGLES, 0, _renderBatch.size());

        render->DisableVertexAttribArray(uvLoc);
        render->DisableVertexAttribArray(posLoc);

        atlas.UnBind();
        program->UnBind();
    }


};
