#include "pch.h"
#include "main.h"

#include "TextureLoader.h"
#include "SceneInitializer.h"

using namespace nam;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    App* app = App::Get(hInstance, 1920, 1080);
    
    TextureLoader::LoadAllTexture(app);
    SceneInitializer::InitScenes(app);

  	app->Run();	
}