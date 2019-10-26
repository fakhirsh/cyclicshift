
#include <System/App.hpp>
#include <ResourceCache/IOManagerDefault.hpp>
#include <Renderer/GL30/GL30Renderer.hpp>
#include <System/WindowManagerLinux.hpp>
#include <Debugging/LogDefault.hpp>

using namespace FEngine;
using namespace std;

int main( void )
{

    App * app = App::Get();

    app->SetIOManager(make_shared<IOManagerDefault>());
    app->SetWindowManager(make_shared<WindowManagerLinux>());
    app->SetLogger(make_shared<LogDefault>());
    app->SetRenderer(make_shared<GL30Renderer>());
    
    app->Initialize("Data/");

    app->RunGameLoop();

    app->Shutdown();

	return 0;
}

