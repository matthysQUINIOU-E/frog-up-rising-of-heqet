#include "pch.h"
#include "SceneGameplay.h"
#include "TextureTag.h"
#include "ColliderTag.h"
#include "Camera.h"
#include "Frog1.h"
#include "Frog2.h"
#include "Dragonfly.h"
#include "Spider.h"
#include "Grasshopper.h"
#include "Checkpoint.h"
#include "Button.h"
#include "SceneLevelChoice.h"
#include "SceneTag.h"
#include "Platform.h"
#include "PressurePlate.h"

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
        box.m_tag = (size)ColliderTag::Ground;
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
    }

    //platforms
    {
        PressurePlate& pp = CreateGameObject<PressurePlate>();
        pp.SetPosition({ 3,2,3 });
        pp.SetToggleMode(false);

        Platform& p = CreateGameObject<Platform>();
        p.SetPosition({ 10,10,10 });
        p.SetWaypoints({ {10,10,10},{15,10,10},{20,20,10} });
        p.SetEventListen(pp.GetEventId());
    }

    {
        GameObject& go = CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,20,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ 0,10,15 });
        go.AddComponent<TransformComponent>(tc);
        BoxColliderComponent& box = go.SetBoxCollider();
        box.m_tag = (size)ColliderTag::Platform;
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
        box.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
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
        BoxColliderComponent& box = go.SetBoxCollider();
        box.m_tag = (size)ColliderTag::Platform;
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
        box.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
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
        BoxColliderComponent& box = go.SetBoxCollider();
        box.m_tag = (size)ColliderTag::Platform;
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
        box.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
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
        BoxColliderComponent& box = go.SetBoxCollider();
        box.m_tag = (size)ColliderTag::Platform;
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
        box.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
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
        tc.SetWorldYPR(0.f, XM_PIDIV4, XM_PIDIV4);
        go.AddComponent<TransformComponent>(tc);
        BoxColliderComponent& box = go.SetBoxCollider();
        box.m_tag = (size)ColliderTag::Platform;
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
        box.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
    }

    {
        GameObject& go = CreateGameObject<GameObject>();
        MeshRendererComponent mrc;
        mrc.CreateMeshInstance();
        mrc.mp_mesh->BuildBox({ 10,10,10 }, { 1,1,1,1 });
        mrc.mp_mesh->SetTexture((size)TextureTag::Dirt);
        go.AddComponent<MeshRendererComponent>(mrc);
        TransformComponent tc;
        tc.SetWorldPosition({ -20,5,0 });
        go.AddComponent<TransformComponent>(tc);
        BoxColliderComponent& box = go.SetBoxCollider();
        box.m_tag = (size)ColliderTag::Platform;
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogEllie);
        box.m_shouldCollideWith.insert((size)ColliderTag::FrogJoel);
        box.m_shouldCollideWith.insert((size)ColliderTag::Tongue);
    }

    //player1
    {
       Frog1& frog = CreateGameObject<Frog1>();
    }

    //player2
    {
        Frog2& frog = CreateGameObject<Frog2>();
    }

    // collectibles
    {
        Dragonfly& dragonfly = CreateGameObject<Dragonfly>();
        TransformComponent& transform = dragonfly.GetComponent<TransformComponent>();
        transform.SetWorldPosition({ 5.0f, 1.0f, 5.0f });
    }
    {
        Dragonfly& spider = CreateGameObject<Dragonfly>();
        TransformComponent& transform = spider.GetComponent<TransformComponent>();
        transform.SetWorldPosition({ -5.0f, 1.0f, 5.0f });
    }
    {
        Dragonfly& grass = CreateGameObject<Dragonfly>();
        TransformComponent& transform = grass.GetComponent<TransformComponent>();
        transform.SetWorldPosition({ -5.0f, 1.0f, -5.0f });
    }

    //checkpoint
    {
        Checkpoint& checkpoint = CreateGameObject<Checkpoint>();
        TransformComponent& transform = checkpoint.GetComponent<TransformComponent>();
        transform.SetWorldPosition({10,21,45});
    }
}

void SceneGameplay::Destroy()
{
    Clear();
}
