#pragma once
#include <GameObject.h>

#include<GuiValue.h>
#include "Bullet.h"
#include "Gauge.h"

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
	enum JumpState
	{
		ON_GROUND,	// �ڒn��
		JUMPING,	// ���񂾏u��
		STAY_IN_AIR,// �؋�
		FALLING,	//	������
	};

private:

	Vector2 mousecenter = Vector2(Library::GetWindowWidth() / 2.0f, 750.0);

	// �e
	static const int BULLET_MAX = 20;
	//std::array<std::shared_ptr<Bullet>, BULLET_MAX>bullets;
	Bullet bullets[BULLET_MAX]{};

	// �W�����v��
	JumpState jump = STAY_IN_AIR;

	// HP
	float HP = 100;

	// HP�Q�[�W
	Gauge HPGauge{};
};

