#include "MoveFloor.h"

MoveFloor::MoveFloor()
	: GameObject("MoveFloor")
{
	modelObjects["main"].Create(MelLib::ModelData::Get(MelLib::ShapeType3D::BOX), GetObjectName());

	moveUp.SetData(20.0f, GetObjectName(), "MoveY", 0.0f, 100.0f);
}

void MoveFloor::Initialize()
{
	// メッシュの判定を取得
	std::vector<std::vector<MelLib::TriangleData>>triData;

	// 移動範囲を設定
	easing = MelLib::Easing<float>(GetPosition().y, GetPosition().y + moveUp.GetValue());

	SetScale(5);
	
}

void MoveFloor::Update()
{
	// イーズインアウトの動きをする
	MelLib::Vector3 pos = GetPosition();

	// addParがMAXになったらaddParをマイナスにする処理を追加する
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
