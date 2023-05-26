#include "Play.h"

#include<GameObjectManager.h>

#pragma region オブジェクト
#include"Player.h"
#include"Stage.h"
#include "BaseEnemy.h"
#pragma endregion


void Play::Initialize()
{
	// オブジェクトのInitializeを呼び出す
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
}

void Play::Update()
{
	MelLib::GameObjectManager::GetInstance()->Update();
}

void Play::Draw()
{
	MelLib::GameObjectManager::GetInstance()->Draw();
}

void Play::Finalize()
{
	// 全削除
	MelLib::GameObjectManager::GetInstance()->AllEraseObject();
}

MelLib::Scene* Play::GetNextScene()
{
	return new Play();
}
