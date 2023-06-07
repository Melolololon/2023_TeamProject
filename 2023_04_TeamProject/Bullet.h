#pragma once
#include <GameObject.h>

using namespace MelLib;

class Bullet : public GameObject
{
public:
	static void LoadResource();

	Bullet();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	/// <summary>
	/// �e��ݒ�
	/// </summary>
	/// <param name="position">�J�n�n�_</param>
	/// <param name="rotation">��ԕ���</param>
	/// <param name="velocityMagnification">���x�̔{��(�����l{ 0, 0, 1})</param>
	/// <param name="power">�U����</param>
	void SetParameter(Vector3 position, float rotation, float velocityMagnification = 1.0f, float power = 1.0f);

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
	const float PI = 3.141592;

public:
	// ���W
	Vector3 position{};
	// ���x
	Vector3 velocity = { 1.0f, 1.0f, 0.0f };
	// �U����
	float power = 0.0f;
	// �J�n�t���[��
	int frame = 0;
	// �I���t���[��
	int end_frame = 100;
};

