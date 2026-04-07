#pragma once
class GameText : public nam::GameObject
{
public:
	void OnInit() override;
	void SetText(std::string text);
	void SetPostion(DirectX::XMFLOAT2 position);
	void SetTextSize(float size);
};

