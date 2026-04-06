#include "pch.h"
#include "Text.h"
#include "GameText.h"

using namespace nam;
using namespace DirectX;

void GameText::OnInit()
{
	AddComponent<TransformComponent>({});
	TextRendererComponent trc;
	trc.CreateTextInstance();
	trc.mp_text->SetDatas({ 40,40 }, 0.7f);
	AddComponent<TextRendererComponent>(trc);
}

void GameText::SetText(std::string text)
{
	TextRendererComponent& trc = GetComponent<TextRendererComponent>();
	trc.mp_text->SetText(text);
}

void GameText::SetPostion(XMFLOAT2 position)
{
	TransformComponent& t = GetComponent<TransformComponent>();
	t.SetWorldPosition({position.x,position.x,0});
}

void GameText::SetTextSize(float size)
{
	TextRendererComponent& trc = GetComponent<TextRendererComponent>();
	trc.mp_text->SetCharacterSize({size,size});
}
