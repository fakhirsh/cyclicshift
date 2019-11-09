
#include <System/App.hpp>
#include <ResourceCache/IOManagerDefault.hpp>
#include <Renderer/GL30/GL30Renderer.hpp>
#include <System/WindowManagerLinux.hpp>
#include <Debugging/LogDefault.hpp>
#include <Graphics2D/Texture.hpp>
#include <Utility/String.hpp>


#include <png.h>
#include <GuillotineBinPack.h>

#include "../../Common/System.hpp"


using namespace FEngine;
using namespace AtlasMaker;
using namespace std;
 
int main(int argc, char ** argv)
{
    App * app = App::Get();
    app->SetIOManager(make_shared<IOManagerDefault>());
    app->SetLogger(make_shared<LogDefault>());
    app->SetAssetDirPrefix("Assets/");
    
    LogPtr log = App::Get()->GetLogger();
    log->Print("Atlas Maker v0.1");
  
    vector<char> buffer;
    string sysConfXMLPath = app->GetAssetDirPrefix() + "SystemConfig.xml";
    app->GetIOManager()->GetAssetStream(sysConfXMLPath, buffer);
    if(!System::Get()->LoadConfig(buffer)){
        log->Print("Error Loading --[ " + sysConfXMLPath + " ]--", "main()");
        return -1;
    }

    System::Get()->GenerateRectanglePacking();
    

    return 0;
}
