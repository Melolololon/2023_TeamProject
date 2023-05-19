#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(const std::string& name)
	:GameObject(name)
{
	MelLib::ModelData::Load("Resource/surakiti/surakiti.obj",false,"surakiti");
	modelObjects["main"].Create(MelLib::ModelData::Get("surakiti"), GetObjectName());
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::Initialize()
{
}

void BaseEnemy::Update()
{
	Move();
}

void BaseEnemy::Draw()
{
	AllDraw();
}

void BaseEnemy::Move()
{
	Vector3 pPos = player->GetPosition();
	Vector3 ePos = GetPosition();
	float rad = atan2(pPos.y - ePos.y, pPos.x - ePos.x);
	moveX = (float)(cos(rad) * moveAmount + ePos.x);
	moveY = (float)(sin(rad) * moveAmount + ePos.y);

	SetPosition({ moveX , moveY , ePos.z });
}
