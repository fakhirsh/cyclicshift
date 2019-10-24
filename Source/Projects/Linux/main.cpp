
#include <System/App.hpp>
#include <ResourceCache/IOManagerDefault.hpp>
#include <Renderer/GL30/GL30Renderer.hpp>
#include <System/WindowManagerLinux.hpp>
#include <Debugging/LogDefault.hpp>

using namespace FEngine;

int main( void )
{

    App * app = App::Get();

    app->SetIOManager(new IOManagerDefault());
    app->SetWindowManager(new WindowManagerLinux());
    app->SetLogger(new LogDefault());
    app->SetRenderer(new GL30Renderer());
    
    app->Initialize("Data/");

    app->RunGameLoop();

    app->Shutdown();

	return 0;
}

