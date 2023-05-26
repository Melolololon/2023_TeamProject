#include "BaseEnemy.h"

std::shared_ptr<BaseEnemy> BaseEnemy::Create(const std::string& name, Player* player) {
	std::shared_ptr<BaseEnemy> enemy = std::make_shared<BaseEnemy>(name);

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
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(GetScale().x / 2);

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
	float angle = 0.0f;
	if (ePos.x < pPos.x) {
		angle = -90.0f;
	}
	else if (ePos.x > pPos.x) {
		angle = 90.0f;
	}

	SetAngle({ 0,angle,0 });
}

void BaseEnemy::Hit(const GameObject& object, const ShapeType3D shapeType, const std::string& shapeName, const ShapeType3D hitObjShapeType, const std::string& hitShapeName)
{
	if (typeid(object) == typeid(Bullet)) {
		Damage();
	}
}

void BaseEnemy::Damage()
{
	Vector3 ePos = GetPosition();
}
