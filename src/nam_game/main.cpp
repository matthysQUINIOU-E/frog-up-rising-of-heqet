#include "pch.h"
#include "main.h"

#include "Camera.h"
#include "Frog1.h"
#include "Frog2.h"

using namespace nam;
using namespace DirectX;

enum class TextureTag : size
{
    _Grass,
    _Dirt
};

enum class SceneTag : size
{
    _Main
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    App* app = App::Get(hInstance, 1920, 1080);
    app->LoadTexture(L"../../res/Textures/dirt.dds", (size)TextureTag::_Dirt);
    app->LoadTexture(L"../../res/Textures/grass.dds", (size)TextureTag::_Grass);

    Scene& scene = app->CreateOrGetScene<Scene>((size)SceneTag::_Main);

    // sun
    {
        GameObject& go = scene.CreateGameObject<GameObject>();
        LightComponent lc;
        lc.CreateLightInstance();
        lc.mp_light->SetToDirectionalLight(0.8f, { 0.f,-1.f,0.f }, { 1.f,0.99f,0.88f });
        go.AddComponent<LightComponent>(lc);
    }

    //camera
    {
        Camera& camera = scene.CreateGameObject<Camera>();
    }

    // plane / ground
    {
        GameObject& go = scene.CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 100.f,0.1f,100.f }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::_Grass);
        go.AddComponent<MeshRendererComponent>(mrc);
        go.AddComponent<TransformComponent>(TransformComponent());
        go.SetBoxCollider();
    }

    //platforms
    {
        GameObject& go = scene.CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,2,10}, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::_Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({0,10,15});
        go.AddComponent<TransformComponent>(tc);
        go.SetBoxCollider();
    }

    {
        GameObject& go = scene.CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,2,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::_Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 0,10,30 });
        go.AddComponent<TransformComponent>(tc);
        go.SetBoxCollider();
    }

    {
        GameObject& go = scene.CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,2,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::_Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 0,20,45 });
        go.AddComponent<TransformComponent>(tc);
        go.SetBoxCollider();
    }

    {
        GameObject& go = scene.CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,2,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::_Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 10,20,45 });
        go.AddComponent<TransformComponent>(tc);
        go.SetBoxCollider();
    }

    {
        GameObject* go = scene->CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,10,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::_Dirt);
        go->AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 0,5,-15 });
        go->AddComponent<TransformComponent>(tc);
        go->SetBoxCollider();
    }

    //player1
    {
        Frog1& frog = scene.CreateGameObject<Frog1>();
    }

    //player2
    {
        Frog2& frog = scene.CreateGameObject<Frog2>();
    }
   
  	app->Run();	
}