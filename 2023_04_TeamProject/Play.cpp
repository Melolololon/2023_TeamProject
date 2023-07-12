#include "Play.h"

#include<GameObjectManager.h>
#include<SceneEditer.h>

#include"Title.h"
#include"Input.h"

#pragma region オブジェクト
#include"Player.h"
#include"Stage.h"
#include"BaseEnemy.h"
#include"Dorakiti.h"
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
	MelLib::Camera::Get()->SetCameraToTargetDistance(70.0f);

	// オブジェクトのInitializeを呼び出す
	//MelLib::GameObjectManager::GetInstance()->InitializeObject();

	// バグ対策
	//MelLib::SceneEditer::GetInstance()->LoadEditData("07_12_Test");
	//MelLib::SceneEditer::GetInstance()->LoadEditData("Stage_Dorakiti");
	//MelLib::GameObjectManager::GetInstance()->AllEraseObject();
//	MelLib::SceneEditer::GetInstance()->LoadEditData("Stage_Dorakiti");


	//MelLib::GameObjectManager::GetInstance()->AddObject(player);
	//MelLib::GameObjectManager::GetInstance()->AddObject(std::make_shared<Stage>());

	//std::vector<std::shared_ptr<Dorakiti>> dorakiti;
	//for (int i = 0; i < 3; i++) {
	//	dorakiti.push_back(Dorakiti::Create("Dorakiti", player.get()));
	//}

	////dorakiti[0]->SetPosition({300,20,0});


	//for (std::shared_ptr<Dorakiti>& enemyObj : dorakiti) {
	//	MelLib::GameObjectManager::GetInstance()->AddObject(enemyObj);
	//}
	gameState = GameState::PLAY;

	player = Player::GetPPlayer();

	BaseEnemy::SetPlayer(player);
	backGround = std::make_unique<BackGround>(player);
	cursorTexture = std::make_unique<CursorTexture>();

	operationSprite.Create(MelLib::Texture::Get("operation"));

	clearStaging.Initialize();
	gameOverStaging.Initialize();

	// テスト
	//MelLib::GameObjectManager::GetInstance()->AddObject(std::make_shared<Goal>(MelLib::Vector3(707,11.0f,1)));

}

void Play::Update()
{
	MelLib::GameObjectManager::GetInstance()->Update();

	// クリア、ゲームオーバーチェック
	if (player->GetClear()) gameState = GameState::CLEAR;
	if (player->GetDead()) gameState = GameState::GAMEOVER;


	Fade::GetInstance()->Update();
	if (Fade::GetInstance()->GetChangeSceneFlag())isEnd = true;
	backGround->Update();
	cursorTexture->Update();

	// 更新切替
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
	backGround->Draw();
	MelLib::GameObjectManager::GetInstance()->Draw();

	cursorTexture->Draw();

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
	// 全削除
	MelLib::GameObjectManager::GetInstance()->AllEraseObject();
}

MelLib::Scene* Play::GetNextScene()
{
	return new Title();
}
