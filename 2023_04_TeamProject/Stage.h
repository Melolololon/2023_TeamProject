#pragma once
#include <GameObject.h>
class Stage :
    public MelLib::GameObject
{
private:
	// ���b�V������O�p�`�̔�����擾
	void SetMeshTriangle();

public:
	Stage();

	void Initialize();

	//�X�V
	void Update();
	//�`��
	void Draw();

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
		const MelLib::ShapeType3D shapeType,
		const std::string& shapeName,
		const MelLib::ShapeType3D hitObjShapeType,
		const std::string& hitShapeName
	);

	std::shared_ptr<GameObject> GetNewPtr();
};

