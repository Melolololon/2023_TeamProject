#pragma once
#include <GameObject.h>

#include<GuiValue.h>

using namespace MelLib;

class Player :
	public GameObject
{
	GuiFloat power;
	GuiFloat speed;

public:
	Player();

	void Initialize() override;

	void Update() override;

	void Draw() override;
};

