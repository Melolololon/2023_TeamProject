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

	// ポインター
	// エディタで配置するのに使う
	std::shared_ptr<GameObject> GetNewPtr() override;

private:

	// 移動
	void Move();
	// ジャンプ
	void Jump();
	// 射撃
	void Shot();

private:

	Vector2 mousecenter = Vector2(Library::GetWindowWidth() / 2.0f, 640.0);
};

