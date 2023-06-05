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


#pragma region �s��ǉ���
	// �A�j���[�V��������p
	enum class ThisState 
	{
		STOP,
		DASH,
		JUMP,
		DEAD,
		CLEAR
	};
#pragma endregion

public:
	static void LoadResource();

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

#pragma region �s��ǉ��֐�
	
	/// <summary>
	/// �ړ��ɂ���]
	/// </summary>
	/// <param name="rotLeft">�����ǂ����Bfalse���ƉE�B</param>
	void MoveRot(const bool rotLeft);

	void Animation();

	/// <summary>
	/// �㔼�g�̃A�j���[�V�����ݒ�
	/// </summary>
	/// <param name="animName">�Z�b�g����A�j���[�V������</param>
	void SetUpperBodyAnimation(const std::string& animName);

	/// <summary>
	/// �S�[��������
	/// </summary>
	void Clear();
#pragma endregion

private:

	Vector2 mousecenter = Vector2(Library::GetWindowWidth() / 2.0f, 640.0);

	// �e
	static const int BULLET_MAX = 20;
	//std::array<std::shared_ptr<Bullet>, BULLET_MAX>bullets;
	Bullet bullets[BULLET_MAX]{};

	// �W�����v��
	bool jumping = false;
	// �ڒn����
	bool onGround = false;
	// �ڒn����(�O�t���[���p)
	bool onGroundPre = false;

#pragma region �s��ǉ��ϐ�

	const MelLib::Vector3 START_ANGLE = MelLib::Vector3(0, 0, 0);
	const MelLib::Vector3 DEFORT_ANGLE = MelLib::Vector3(0, -90, 0);

	// �V���b�g�A�j���[�V���������蓖�Ă�{�[��
	const std::vector<std::string> SET_SHOT_ANIM_BONE =
	{
		"R_Arm_1",
		"R_Arm_2",
		"R_Arm_3",
		"L_Arm_1",
		"L_Arm_2",
		"L_Arm_3",
		"Head",
	};

	// ���g�̏��
	ThisState thisState = ThisState::STOP;

	// �V���b�g�����ǂ���
	// �V���b�g�ƈړ��Ȃǂ̂��̑��s����������̂ŁA�ʂɃt���O��p��
	bool isShot = false;
#pragma endregion
};

