#include "Dorakiti.h"

std::shared_ptr<Dorakiti> Dorakiti::Create(const std::string& name, Player* player) {
	std::shared_ptr<Dorakiti> enemy = std::make_shared<Dorakiti>(name);

	enemy->SetPlayer(player);
	enemy->SetPosition({ static_cast<float>(rand() % 10),0.0f,0.0f });

	return enemy;
}


Dorakiti::Dorakiti(const std::string& name)
	:BaseEnemy(name)
{
	//MelLib::ModelData::Load("Resource/" + name + "/" + name + ".obj", false, name);
	//modelObjects["main"].Create(MelLib::ModelData::Get(name), GetObjectName());
	easing = MelLib::Easing<float>(0.1f, -0.1f, 0.5f);
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

	moveX -= 0.01f;
	moveY += easing.EaseInOut();

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