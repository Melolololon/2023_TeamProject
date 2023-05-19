#include "Stage.h"

void Stage::SetMeshTriangle()
{
	std::vector<std::vector<MelLib::TriangleData>> triDatas;
	modelObjects["main"].GetModelTriangleData(triDatas);

	triangleDatas["main"].reserve(triDatas[0].size());
	
	// 判定を格納
	for (size_t i = 0; i < triDatas[0].size(); i++)
	{
		MelLib::TriangleData& t = triDatas[0][i];

		// 横は無視
		if (t.GetNormal().z != 0.0f)continue;

		triangleDatas["main"].push_back(t);
	}

	triangleDatas["main"].shrink_to_fit();
}

Stage::Stage():GameObject("Stage")
{
	modelObjects["main"].Create(MelLib::ModelData::Get("Stage"),GetObjectName());
}

void Stage::Initialize()
{
	// メッシュをセット
	SetMeshTriangle();
}

void Stage::Update()
{
}

void Stage::Draw()
{
}

void Stage::Hit(const GameObject& object, const MelLib::ShapeType3D shapeType, const std::string& shapeName, const MelLib::ShapeType3D hitObjShapeType, const std::string& hitShapeName)
{

}

std::shared_ptr<MelLib::GameObject> Stage::GetNewPtr()
{
	return std::make_shared<Stage>();
}
