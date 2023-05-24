#include "Goal.h"

#include"Player.h"

Goal::Goal()
	:GameObject("Goal")
{
	modelObjects["main"].Create(MelLib::ModelData::Get(""), GetObjectName());
}

void Goal::Initialize()
{
	// ������
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(10.0f);
}
