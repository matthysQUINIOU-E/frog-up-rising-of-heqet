#pragma once
#include "SpriteRendererComponent.h"

enum class Type : nam::size
{
	Jauge0,
	Jauge1, 
	Jauge2, 
	Jauge3, 
	Jauge4, 
	Jauge5, 
	Size
};

class Jauge : public nam::GameObject
{
public:
	void OnInit() override;
	void SetJauge(Type type);
	void Update();
private:
	SpriteRendererComponent m_src;
	Type m_type;
	Type m_previousType;
};

