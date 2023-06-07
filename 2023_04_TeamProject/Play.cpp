#include "Play.h"

#include<GameObjectManager.h>

#include"Title.h"

#pragma region �I�u�W�F�N�g
#include"Player.h"
#include"Stage.h"
#include "BaseEnemy.h"
#include"Goal.h"
#pragma endregion

#include"Fade.h"

void Play::ClearUpdate()
{
	clearStaging.Update();

	if (clearStaging.GetSceneChangeFlag())Fade::GetInstance()->Start();
}

void Play::ClearDraw()
{
	clearStaging.Draw();
}

void Play::GameOverUpdate()
{
	gameOverStaging.Update();

	if (gameOverStaging.GetSceneChangeFlag())Fade::GetInstance()->Start();
}

void Play::GameOverDraw()
{
	gameOverStaging.Draw();
}

void Play::Initialize()
{
	MelLib::Camera::Get()->SetCameraToTargetDistance(50.0f);

	// �I�u�W�F�N�g��Initialize���Ăяo��
	//MelLib::GameObjectManager::GetInstance()->InitializeObject();

	player = std::make_shared<Player>();
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

	clearStaging.Initialize();
	gameOverStaging.Initialize();

	// �e�X�g
	MelLib::GameObjectManager::GetInstance()->AddObject(std::make_shared<Goal>(MelLib::Vector3(10,0,0)));
}

void Play::Update()
{
	MelLib::GameObjectManager::GetInstance()->Update();

	// �N���A�A�Q�[���I�[�o�[�`�F�b�N
	if (player->GetClear()) gameState = GameState::CLEAR;
	if (player->GetDead()) gameState = GameState::GAMEOVER;


	Fade::GetInstance()->Update();
	if (Fade::GetInstance()->GetChangeSceneFlag())isEnd = true;

	// �X�V�ؑ�
	switch (gameState)
	{
	case Play::GameState::CLEAR:
		ClearUpdate();
		break;
	case Play::GameState::GAMEOVER:
		GameOverUpdate();
		break;
	default:
		break;
	}
}

void Play::Draw()
{
	backGround.Draw();
	MelLib::GameObjectManager::GetInstance()->Draw();

	if(gameState == Play::GameState::PLAY) operationSprite.Draw();

	switch (gameState)
	{
	case Play::GameState::CLEAR:
		ClearDraw();
		break;
	case Play::GameState::GAMEOVER:
		GameOverDraw();
		break;
	default:
		break;
	}

	Fade::GetInstance()->Draw();
}

void Play::Finalize()
{
	// �S�폜
	MelLib::GameObjectManager::GetInstance()->AllEraseObject();
}

MelLib::Scene* Play::GetNextScene()
{
	return new Title();
}
