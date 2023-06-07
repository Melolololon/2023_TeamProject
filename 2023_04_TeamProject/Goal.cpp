#include "Goal.h"

void Goal::LoadResource()
{
	MelLib::ModelData::Load("Resource/goal/goal_2.obj",false,"Goal");
}

Goal::Goal(const MelLib::Vector3& pos):GameObject("Goal")
{

	modelObjects["main"].Create(MelLib::ModelData::Get("Goal"), GetObjectName());
	SetScale({ 7,7,7 });
	SetAngle({ 0,180,0 });
	SetPosition(pos);
	//AddPosition({ 0,-0.5f,1 });
}

void Goal::Initialize()
{
	// ������쐬
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition() + MelLib::Vector3(0, -6, -1));

	// �킴�Ə����߂ɂ��Ă���
	sphereDatas["main"][0].SetRadius(0.1f);
}
