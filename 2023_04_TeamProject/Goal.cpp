#include "Goal.h"

void Goal::LoadResource()
{
	MelLib::ModelData::Load("Resource/goal/goal_2.obj",false,"Goal");
}

Goal::Goal():GameObject("Goal")
{
	modelObjects["main"].Create(MelLib::ModelData::Get("Goal"), GetObjectName());

}

void Goal::Initialize()
{
	// îªíËÇçÏê¨
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(2.0f);
}
