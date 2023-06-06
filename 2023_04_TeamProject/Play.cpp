#include "Play.h"

#include<GameObjectManager.h>

#pragma region �I�u�W�F�N�g
#include"Player.h"
#include"Stage.h"
#include "BaseEnemy.h"
#include"Goal.h"
#pragma endregion


void Play::Initialize()
{
	// �I�u�W�F�N�g��Initialize���Ăяo��
	//MelLib::GameObjectManager::GetInstance()->InitializeObject();

	std::shared_ptr<Player> player = std::make_shared<Player>();
	MelLib::GameObjectManager::GetInstance()->AddObject(player);
	MelLib::GameObjectManager::GetInstance()->AddObject(std::make_shared<Stage>());

	std::list<std::shared_ptr<BaseEnemy>> enemy;
	for (int i = 0; i < 5; i++) {
		enemy.push_back(BaseEnemy::Create("surakiti", player.get()));
	}

	for (std::shared_ptr<BaseEnemy>& enemyObj : enemy) {
		MelLib::GameObjectManager::GetInstance()->AddObject(enemyObj);
	}


	operationSprite.Create(MelLib::Texture::Get("operation"));

	// �e�X�g
	MelLib::GameObjectManager::GetInstance()->AddObject(std::make_shared<Goal>(MelLib::Vector3(10,0,0)));
}

void Play::Update()
{
	MelLib::GameObjectManager::GetInstance()->Update();
}

void Play::Draw()
{
	backGround.Draw();
	MelLib::GameObjectManager::GetInstance()->Draw();
	operationSprite.Draw();
}

void Play::Finalize()
{
	// �S�폜
	MelLib::GameObjectManager::GetInstance()->AllEraseObject();
}

MelLib::Scene* Play::GetNextScene()
{
	return new Play();
}
