#include "Goal.h"

void Goal::LoadResource()
{
	// ƒ‚ƒfƒ‹–³‚¢‚©‚ç•·‚­
	MelLib::ModelData::Load("",false,"Goal");
}

Goal::Goal():GameObject("Goal")
{
	modelObjects["main"].Create(MelLib::ModelData::Get("Goal"), GetObjectName());

}

void Goal::Initialize()
{
	// ”»’è‚ğì¬
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(2.0f);
}
