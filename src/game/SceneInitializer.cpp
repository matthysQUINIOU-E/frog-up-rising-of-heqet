#include "pch.h"
#include "SceneInitializer.h"

#include "SceneTag.h"

#include "SceneGameplay.h"
#include "SceneLevelChoice.h"

using namespace nam;

void SceneInitializer::InitScenes(nam::App* app)
{
    SceneGameplay& scenegp = app->CreateOrGetScene<SceneGameplay>((size)SceneTag::Gameplay);
    scenegp.SetActive(false);

    SceneLevelChoice& scenelvlc = app->CreateOrGetScene<SceneLevelChoice>((size)SceneTag::LevelChoice);
}
