#include "Gauge.h"

void Gauge::Initialize(Color color, Vector2 scale, float valueMax)
{
	sprite.Create(color);
	sprite.SetScale(scale);
	this->valueMax = valueMax;
}

void Gauge::Update()
{
	float rate = 0;
	rate = *value / valueMax;
	Vector2 scale = sprite.GetScale();
	scale.x = *value;
	//scale.x = rate;

	sprite.SetScale(scale);
}

void Gauge::Draw()
{
	sprite.Draw();
}
