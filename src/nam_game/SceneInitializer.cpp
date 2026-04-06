#include "pch.h"
#include "SceneInitializer.h"

#include "SceneTag.h"

#include "SceneCustomization.h"
#include "SceneGuide.h"
#include "SceneGameplay.h"
#include "SceneLevelChoice.h"
#include "SceneNextLevel.h"
#include "SceneOption.h"
#include "ScenePause.h"
#include "SceneProfil.h"
#include "SceneVictory.h"

using namespace nam;

void SceneInitializer::InitScenes(nam::App* app)
{
    SceneCustomization& sceneCusto = app->CreateOrGetScene<SceneCustomization>((size)SceneTag::Customisation);
    sceneCusto.SetActive(false);

    SceneGuide& sceneGuide = app->CreateOrGetScene<SceneGuide>((size)SceneTag::Guide);
    sceneGuide.SetActive(false);

    SceneGameplay& sceneGp = app->CreateOrGetScene<SceneGameplay>((size)SceneTag::Gameplay);
    sceneGp.SetActive(false);

    SceneLevelChoice& sceneLevelChoice = app->CreateOrGetScene<SceneLevelChoice>((size)SceneTag::LevelChoice);
    sceneLevelChoice.SetActive(false);

    SceneNextLevel& sceneNextLevel = app->CreateOrGetScene<SceneNextLevel>((size)SceneTag::NextLevel);
    sceneNextLevel.SetActive(false);

    SceneOption& sceneOption = app->CreateOrGetScene<SceneOption>((size)SceneTag::Option);
    sceneOption.SetActive(false);

    ScenePause& scenePause = app->CreateOrGetScene<ScenePause>((size)SceneTag::Pause);
    scenePause.SetActive(false);

    SceneVictory& sceneVictory = app->CreateOrGetScene<SceneVictory>((size)SceneTag::Victory);
    sceneVictory.SetActive(false);

    SceneProfil& sceneProfil = app->CreateOrGetScene<SceneProfil>((size)SceneTag::Profil);
}
