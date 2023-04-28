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
	// ���W
	Vector3 position{};
	// ���x
	Vector3 velocity = { 1.0f, 0.0f, 0.0f };
	// �U����
	float power = 0.0f;
	// �J�n�t���[��
	int frame = 0;
	// �I���t���[��
	int end_frame = 100;
};

