#include "Stage.h"


float Stage::deadPositionY = FLT_MAX;

void Stage::SetMeshTriangle()
{
	std::vector<std::vector<MelLib::TriangleData>> triDatas;
	modelObjects["main"].GetModelTriangleData(triDatas);

	size_t allTriSize = 0;
	for (const auto tri : triDatas) 
	{
		allTriSize += tri.size();
	}
	triangleDatas["main"].reserve(allTriSize);
	
	// 判定を格納
	for (size_t i = 0; i < triDatas.size(); i++) 
	{
		for (size_t j = 0; j < triDatas[i].size(); j++)
		{
			MelLib::TriangleData& tri = triDatas[i][j];

			// 横は無視
			//if (t.GetNormal().x != 0.0f)continue;

			triangleDatas["main"].push_back(tri);

			// ステージの一番低い座標を格納
			if (deadPositionY >= tri.GetPosition().v1.y)
			{
				deadPositionY = tri.GetPosition().v1.y;
			}
		}
	}

	triangleDatas["main"].shrink_to_fit();
}

Stage::Stage(const short stageNum) :GameObject("Stage" + std::to_string(stageNum))
, STAGE_NUM(stageNum)
{
	modelObjects["main"].Create(MelLib::ModelData::Get("Stage" + std::to_string(stageNum)),GetObjectName());
	
	// これのせいででかくした時判定バグってる可能性大
	addPosY.SetData(0, "StageTestWindow", "AddPosY", -200, 20);

	deadPositionY = FLT_MAX;
}

void Stage::Initialize()
{
	// メッシュをセット
	SetMeshTriangle();


	SetAngle({ 0, 270, 00 });
	//SetPosition({ 0,-40 + addPosY.GetValue(),0 });

}

void Stage::Update()
{
}

void Stage::Draw()
{
	AllDraw();
}

void Stage::Hit(const GameObject& object, const MelLib::ShapeType3D shapeType, const std::string& shapeName, const MelLib::ShapeType3D hitObjShapeType, const std::string& hitShapeName)
{
}

std::shared_ptr<MelLib::GameObject> Stage::GetNewPtr()
{
	return std::make_shared<Stage>(STAGE_NUM);
}
