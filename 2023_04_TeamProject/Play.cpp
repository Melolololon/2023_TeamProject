#include "Play.h"

#include<GameObjectManager.h>

void Play::Initialize()
{
}

void Play::Update()
{
}

void Play::Draw()
{
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
