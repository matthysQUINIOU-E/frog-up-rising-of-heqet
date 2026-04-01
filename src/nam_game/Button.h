#pragma once
#include "ButtonType.h"

class Button : public nam::GameObject
{
private:
	ButtonType m_buttonType = ButtonType::Play;
	std::function<void()> m_onClick = nullptr;
public:
	void SetButtonType(ButtonType buttonType);
	void SetOnClick(std::function<void()> onClick);
	void SetPosition(DirectX::XMFLOAT2 position);

	void OnInit() override;
	void OnClick();
	void OnHovered();
	void OnLeft();
};

