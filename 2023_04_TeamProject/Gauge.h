#pragma once
#include "Sprite2D.h"

using namespace MelLib;

// ƒQ[ƒW
class Gauge
{
public:
	void Initialize(Color color, Vector2 scale, float valueMax);

	void Update();

	void Draw();

	void SetValue(float* value){
		this->value = value;
	}

	void SetPosition(Vector2 position) { sprite.SetPosition(position); }

private:
	Sprite2D sprite;
	float* value;
	float valueMax = 0;
};