
#include <Debugging/LogDefault.hpp>
#include <Renderer/GLES20/GLES20Renderer.hpp>
#include <ResourceCache/IOManagerDefault.hpp>
#include <System/App.hpp>
#include <System/WindowManagerWeb.hpp>

using namespace std;
using namespace FEngine;

int main( int argc, char ** argv )
{
 
    App * app = App::Get();

    app->SetIOManager(make_shared<IOManagerDefault>());
    app->SetWindowManager(make_shared<WindowManagerWeb>());
    app->SetLogger(make_shared<LogDefault>());
    app->SetRenderer(make_shared<GLES20Renderer>());
    
    app->SetAssetDirPrefix("Data/");
    app->Initialize();

    app->RunGameLoop();

    app->Shutdown();

    return 0;
}

