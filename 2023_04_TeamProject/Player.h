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

	/// <summary>
	/// �Փ˂������ɌĂяo����锻��
	/// </summary>
	/// <param name="object">�I�u�W�F�N�g</param>
	/// <param name="shapeType">�����̂ǂ̌`��̔���Ɠ���������</param>
	/// <param name="shapeName">���薼</param>
	/// <param name="hitObjShapeType">����̌`��</param>
	/// <param name="hitShapeName">����̔��薼</param>
	void Hit
	(
		const GameObject& object,
		const ShapeType3D shapeType,
		const std::string& shapeName,
		const ShapeType3D hitObjShapeType,
		const std::string& hitShapeName
	) override;

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

