#include "Play.h"

#include<GameObjectManager.h>

void Play::Initialize()
{
	// オブジェクトのInitializeを呼び出す
	//MelLib::GameObjectManager::GetInstance()->InitializeObject();
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
