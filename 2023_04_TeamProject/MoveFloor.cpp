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
	easing = MelLib::Easing<float>(GetPosition().y, GetPosition().y + moveUp.GetMaxValue(), 0.5f);

	SetScale(5);
	
}

void MoveFloor::Update()
{
	// イーズインアウトの動きをする
	MelLib::Vector3 pos = GetPosition();

	// addParがMAXになったらaddParをマイナスにする処理を追加する
	pos.y = easing.EaseInOut();
	SetPosition(pos);
}

std::shared_ptr<MelLib::GameObject> MoveFloor::GetNewPtr()
{
	return std::make_shared<MoveFloor>();
}
