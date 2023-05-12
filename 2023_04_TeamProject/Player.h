#pragma once
#include <GameObject.h>

#include<GuiValue.h>
#include "Bullet.h"

using namespace MelLib;

class Player : public GameObject
{
	GuiFloat power;
	GuiFloat speed;
	GuiFloat gravity;

public:
	Player();

	void Initialize() override;

	void Update() override;

	void Draw() override;

private:

	// ˆÚ“®
	void Move();
	// ƒWƒƒƒ“ƒv
	void Jump();
	// ŽËŒ‚
	void Shot();
};

