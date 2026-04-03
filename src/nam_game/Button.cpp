#include "pch.h"
#include "Button.h"
#include <SpriteManager.h>

using namespace nam;

void Button::SetButtonType(ButtonType buttonType)
{
	m_buttonType = buttonType;
	OnLeft();
}

void Button::SetOnClick(std::function<void()> onClick)
{
	m_onClick = onClick;
}

void Button::SetPosition(DirectX::XMFLOAT2 position)
{
	TransformComponent& transform = GetComponent<TransformComponent>();
	transform.SetWorldPosition({ position.x,position.y,0 });
}

void Button::OnInit()
{
	SpriteRendererComponent src;
	src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonPlay0);
	TransformComponent transform;
	AddComponent(src);
	AddComponent(transform);
	SetButton();
}

void Button::OnClick()
{
	if (m_onClick != nullptr)
		m_onClick();
}

void Button::OnHovered()
{
	SpriteRendererComponent& src = GetComponent<SpriteRendererComponent>();

	switch (m_buttonType)
	{
	case ButtonType::Cog:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonCog1);
		break;
	case ButtonType::Left:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonLeft1);
		break;
	case ButtonType::Right:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonRight1);
		break;
	case ButtonType::ReturnLeft:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonReturnLeft1);
		break;
	case ButtonType::ReturnRight:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonReturnRight1);
		break;
	case ButtonType::Trash:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonTrash1);
		break;
	case ButtonType::User:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonUser1);
		break;
	case ButtonType::Valid:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonValid1);
		break;
	case ButtonType::X:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonX1);
		break;
	case ButtonType::Question:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonQuestion1);
		break;
	case ButtonType::Play:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonPlay1);
		break;
	case ButtonType::List:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonList1);
		break;
	default:
		break;
	}
}

void Button::OnLeft()
{
	SpriteRendererComponent& src = GetComponent<SpriteRendererComponent>();

	switch (m_buttonType)
	{
	case ButtonType::Cog:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonCog0);
		break;
	case ButtonType::Left:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonLeft0);
		break;
	case ButtonType::Right:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonRight0);
		break;
	case ButtonType::ReturnLeft:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonReturnLeft0);
		break;
	case ButtonType::ReturnRight:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonReturnRight0);
		break;
	case ButtonType::Trash:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonTrash0);
		break;
	case ButtonType::User:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonUser0);
		break;
	case ButtonType::Valid:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonValid0);
		break;
	case ButtonType::X:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonX0);
		break;
	case ButtonType::Question:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonQuestion0);
		break;
	case ButtonType::Play:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonPlay0);
		break;
	case ButtonType::List:
		src.mp_sprite = SpriteManager::GetSprite(SpriteTag::ButtonList0);
		break;
	default:
		break;
	}
}