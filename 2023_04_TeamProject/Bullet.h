#pragma once
#include <GameObject.h>

using namespace MelLib;

class Bullet : public GameObject
{
public:
	Bullet();

	void Initialize() override;

	void Update() override;

	void Draw() override;

public:
	// 座標
	Vector3 position{};
	// 速度
	Vector3 velocity = { 1.0f, 0.0f, 0.0f };
	// 攻撃力
	float power = 0.0f;
	// 開始フレーム
	int frame = 0;
	// 終了フレーム
	int end_frame = 100;
};

