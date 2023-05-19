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

	// �|�C���^�[
	// �G�f�B�^�Ŕz�u����̂Ɏg��
	std::shared_ptr<GameObject> GetNewPtr() override;

private:

	// �ړ�
	void Move();
	// �W�����v
	void Jump();
	// �ˌ�
	void Shot();

private:

	Vector2 mousecenter = Vector2(Library::GetWindowWidth() / 2.0f, 640.0);
};

