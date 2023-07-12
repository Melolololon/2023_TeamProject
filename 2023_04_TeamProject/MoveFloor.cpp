#include "MoveFloor.h"

MoveFloor::MoveFloor()
	: GameObject("MoveFloor")
{
	modelObjects["main"].Create(MelLib::ModelData::Get(MelLib::ShapeType3D::BOX), GetObjectName());

	moveUp.SetData(20.0f, GetObjectName(), "MoveY", 0.0f, 100.0f);
}

void MoveFloor::Initialize()
{
	// ���b�V���̔�����擾
	std::vector<std::vector<MelLib::TriangleData>>triData;

	// �ړ��͈͂�ݒ�
	easing = MelLib::Easing<float>(GetPosition().y, GetPosition().y + moveUp.GetValue());

	SetScale(5);
	
}

void MoveFloor::Update()
{
	// �C�[�Y�C���A�E�g�̓���������
	MelLib::Vector3 pos = GetPosition();

	// addPar��MAX�ɂȂ�����addPar���}�C�i�X�ɂ��鏈����ǉ�����
	const float FRAME_ADD_PAR = 0.75f;
	const float ADD_PAR = easing.GetPar();
	if(ADD_PAR >= 100.0f)
	{
		easing.SetAddPar(-FRAME_ADD_PAR);
	}
	else if(ADD_PAR <= 0)
	{
		easing.SetAddPar(FRAME_ADD_PAR);
	}
	pos.y = easing.EaseInOut();
	SetPosition(pos);
}

std::shared_ptr<MelLib::GameObject> MoveFloor::GetNewPtr()
{
	return std::make_shared<MoveFloor>();
}
