#include "Dorakiti.h"

std::shared_ptr<Dorakiti> Dorakiti::Create(const std::string& name, Player* player) {
	std::shared_ptr<Dorakiti> enemy = std::make_shared<Dorakiti>(name);

	enemy->SetPlayer(player);
	//enemy->SetPosition({ static_cast<float>(rand() % 10),0.0f,0.0f });

	return enemy;
}


Dorakiti::Dorakiti(const std::string& name)
	:BaseEnemy(name)
{
	//MelLib::ModelData::Load("Resource/" + name + "/" + name + ".obj", false, name);
	//modelObjects["main"].Create(MelLib::ModelData::Get(name), GetObjectName());
	modelObjects["main"].Create(MelLib::ModelData::Get(name), GetObjectName());
	easing = MelLib::Easing<float>(GetPosition().y + 4.1f, GetPosition().y + 30.0f, 0.5f);
	
}

void Dorakiti::Initialize()
{
	//AddPosition({ 0,7,0 });
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(1.5f);

}

void Dorakiti::Move()
{
	Vector3 pPos = player->GetPosition();
	Vector3 ePos = GetPosition();
	float rad = atan2(pPos.y - ePos.y, pPos.x - ePos.x);

	//if (moveY <= -1.0f) {
	if (easing.GetPar() <= 0.5f) {
		easing.SetAddPar(0.5f);
	}
	else if (easing.GetPar() >= 99.5f) {
		easing.SetAddPar(-0.5f);
	}

	//moveX -= 0.01f;
	moveY = easing.EaseInOut();

	SetPosition({ moveX , moveY , ePos.z });
	float angle = 65.0f;

	SetAngle({ 0,angle,0 });
}



std::shared_ptr<GameObject> Dorakiti::GetNewPtr()
{
	return std::make_shared<Dorakiti>("Dorakiti");
}
