#include "Play.h"

#include<GameObjectManager.h>

#pragma region オブジェクト
#include"Player.h"
#include"Stage.h"
#pragma endregion


void Play::Initialize()
{
	// オブジェクトのInitializeを呼び出す
	//MelLib::GameObjectManager::GetInstance()->InitializeObject();


	//MelLib::GameObjectManager::GetInstance()->AddObject(std::make_shared<Player>());
	//MelLib::GameObjectManager::GetInstance()->AddObject(std::make_shared<Stage>());
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
