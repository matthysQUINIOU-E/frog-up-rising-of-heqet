#pragma once
#include "SpriteRendererComponent.h"

enum class JaugeType : nam::size
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
	void SetJauge(JaugeType type);
	void Update();
private:
	nam::SpriteRendererComponent m_src;
	JaugeType m_type;
	JaugeType m_previousType;
};

