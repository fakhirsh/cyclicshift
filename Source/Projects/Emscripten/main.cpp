
#include <System/App.hpp>
#include <System/WindowManagerWeb.hpp>
#include <Renderer/GLES20/GLES20Renderer.hpp>
#include <ResourceCache/IOManagerDefault.hpp>
#include <Debugging/LogDefault.hpp>

using namespace std;
using namespace FEngine;

int main()
{
 
    App * app = App::Get();

    app->SetIOManager(new IOManagerDefault());
    app->SetWindowManager(new WindowManagerWeb());
    app->SetLogger(new LogDefault());
    app->SetRenderer(new GLES20Renderer());
    
    app->Initialize("Data/");

    app->RunGameLoop();

    app->Shutdown();

    return 0;
}

