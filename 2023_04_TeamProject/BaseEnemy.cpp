#include "BaseEnemy.h"

Player* BaseEnemy::player;

std::shared_ptr<BaseEnemy> BaseEnemy::Create(const std::string& name, Player* player) {
	std::shared_ptr<BaseEnemy> enemy = std::make_shared<BaseEnemy>(name);

	enemy->SetPlayer(player);
	enemy->SetPosition({ static_cast<float>(rand() % 10),0.0f,0.0f });

	return enemy;
}


BaseEnemy::BaseEnemy(const std::string& name)
	:GameObject(name)
{
	/*MelLib::ModelData::Load("Resource/" + name + "/" + name + ".obj", false, name);
	modelObjects["main"].Create(MelLib::ModelData::Get(name), GetObjectName());*/
	
	if(typeid(*this) == typeid(BaseEnemy)) modelObjects["main"].Create(MelLib::ModelData::Get(name), GetObjectName());

	//tags.push_back("Enemy");
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::Initialize()
{
	//AddPosition({ 0,10,0 });

	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(GetScale().x / 2);

	MelLib::Value2<MelLib::Vector3>segmentPos;
	float offset = 0.01f;

	
}

void BaseEnemy::Update()
{
	FallStart(0.0f);
	CalcMovePhysics();
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
	if (typeid(object) == typeid(Bullet)
		|| typeid(object) == typeid(Player)) {
		//Damage();
		eraseManager = true;
	}


}

void BaseEnemy::Damage()
{
	Vector3 ePos = GetPosition();
}

std::shared_ptr<GameObject> BaseEnemy::GetNewPtr()
{
	return std::make_shared<BaseEnemy>("surakiti");
}
