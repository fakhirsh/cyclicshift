
#include <Debugging/LogDefault.hpp>
#include <Renderer/GL30/GL30Renderer.hpp>
#include <ResourceCache/IOManagerDefault.hpp>
#include <System/App.hpp>
#include <System/WindowManagerLinux.hpp>

using namespace std;
using namespace FEngine;

int main( int argc, char ** argv )
{

    App * app = App::Get();

    app->SetIOManager(make_shared<IOManagerDefault>());
    app->SetWindowManager(make_shared<WindowManagerLinux>());
    app->SetLogger(make_shared<LogDefault>());
    app->SetRenderer(make_shared<GL30Renderer>());
    
    app->SetAssetDirPrefix("Data/");
    app->Initialize();

    app->RunGameLoop();

    app->Shutdown();

	return 0;
}

