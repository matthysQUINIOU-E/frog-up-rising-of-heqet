#include "pch.h"
#include "SceneGameplay.h"
#include <TextureTag.h>
#include <ColliderTag.cpp>
#include <Camera.h>
#include <Frog1.h>
#include <Frog2.h>
#include <Collectible.h>

using namespace nam;
using namespace DirectX;

void SceneGameplay::Init()
{
    {
        GameObject& go = CreateGameObject<GameObject>();
        LightComponent lc;
        lc.CreateLightInstance();
        lc.mp_light->SetToDirectionalLight(0.8f, { 0.f,-1.f,0.f }, { 1.f,0.99f,0.88f });
        go.AddComponent<LightComponent>(lc);
    }

    //camera
    {
        Camera& camera = CreateGameObject<Camera>();
    }

    // plane / ground
    {
        GameObject& go = CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 100.f,0.1f,100.f }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::Grass);
        go.AddComponent<MeshRendererComponent>(mrc);
        go.AddComponent<TransformComponent>(TransformComponent());
        BoxColliderComponent& box = go.SetBoxCollider();
        box.m_tag = (size)ColliderTag::Platform;
    }

    //platforms
    {
        GameObject& go = CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,2,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 0,10,15 });
        go.AddComponent<TransformComponent>(tc);
        go.SetBoxCollider();
    }

    {
        GameObject& go = CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,2,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 0,10,30 });
        go.AddComponent<TransformComponent>(tc);
        go.SetBoxCollider();
    }

    {
        GameObject& go = CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,2,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 0,20,45 });
        go.AddComponent<TransformComponent>(tc);
        go.SetBoxCollider();
    }

    {
        GameObject& go = CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,2,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 10,20,45 });
        go.AddComponent<TransformComponent>(tc);
        go.SetBoxCollider();
    }

    {
        GameObject& go = CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,10,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 0,5,-15 });
        go.AddComponent<TransformComponent>(tc);
        go.SetBoxCollider();
    }

    //player1
    {
        Frog1& frog = CreateGameObject<Frog1>();
    }

    //player2
    {
        Frog2& frog = CreateGameObject<Frog2>();
    }

    //collectible
    {
        Collectible& collectible = CreateGameObject<Collectible>();
        collectible.SetPosition({ 0.0f, 0.5f, 10.0f });
    }
}

void SceneGameplay::Destroy()
{
    Clear();
}
