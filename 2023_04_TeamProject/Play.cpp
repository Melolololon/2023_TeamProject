#include "Play.h"

#include<GameObjectManager.h>

void Play::Initialize()
{
	// �I�u�W�F�N�g��Initialize���Ăяo��
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
	// �S�폜
	MelLib::GameObjectManager::GetInstance()->AllEraseObject();
}

MelLib::Scene* Play::GetNextScene()
{
	return new Play();
}
