#pragma once
class ButtonExemple : public nam::GameObject
{
public:
	void OnInit() override;
	void OnClick();
	void OnHovered();
	void OnLeft();
};

