#include "BaseEnemy.h"

std::unique_ptr<BaseEnemy> BaseEnemy::Create(const std::string& name, Player* player) {
	std::unique_ptr<BaseEnemy> enemy = std::make_unique<BaseEnemy>(name);

	enemy->SetPlayer(player);
	enemy->SetPosition({static_cast<float>(rand() % 10),0.0f,0.0f});

	return enemy;
}


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
	SetAngle({ 0,DirectX::XMConvertToDegrees(rad) - 90.0f,0 });
}
