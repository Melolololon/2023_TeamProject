#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "BaseEnemy.h"
#include "Stage.h"
#include"Goal.h"

#include"ClearStaging.h"

#pragma region ライブラリインクルード

#include<Library.h>
#include<SceneManager.h>
#include<GameObjectManager.h>
#include<Input.h>
#include<ImguiManager.h>
#include<SceneEditer.h>

#pragma endregion

#include"Title.h"
#include"Play.h"

Game::Game() {}

Game::~Game() {}
Game* Game::GetInstance()
{
	static Game game;
	return &game;
}

Player* player;
//BaseEnemy* enemy;
std::list<std::unique_ptr<BaseEnemy>> enemy;



void Game::Run()
{
	MelLib::ImguiManager::GetInstance()->SetReleaseDrawFlag(true);

	Initialize();

	while (1)
	{
		MelLib::Library::LoopStartProcess();

		if (MelLib::Input::KeyTrigger(DIK_ESCAPE))MelLib::Library::EndFlagTrue();
		if (MelLib::Library::GetIsEnd())break;

		//ImGui::ShowDemoWindow();

		Update();
		Draw();
		MelLib::Library::LoopEndProcess();

	}

	Finalize();
}

void Game::Initialize()
{

	MelLib::Library::Initialize(1920, 1080, MelLib::Color(0, 0, 255, 255), L"MELLib");
	MelLib::Library::SetFramesPerSecond60(true);

#pragma region マネージャー初期化

	/*CollisionFlag initFlag;
	initFlag.board = true;
	initFlag.box = true;
	initFlag.lineSegment = true;
	initFlag.plane = true;
	initFlag.ray = true;
	initFlag.sphere = true;
	GameObjectManager::GetInstance()->SetCollisionFlag3D(initFlag);*/
	MelLib::GameObjectManager::GetInstance()->SetMouseCollisionFlag(true);
	MelLib::GameObjectManager::GetInstance()->ReserveObjectArray(100);

	MelLib::SceneEditer::GetInstance()->SetEditerFlag(false);
	MelLib::SceneEditer::GetInstance()->Initialize();
	//MelLib::SceneEditer::GetInstance()->RegisterObject(std::make_shared<>);
#pragma endregion



	//player = new Player();
	//player->Initialize();
	/*for (int i = 0; i < 3; i++) {
		enemy.push_back(BaseEnemy::Create("surakiti", player));
	}*/


	MelLib::Camera::Get()->SetRotatePoint(MelLib::Camera::RotatePoint::ROTATE_POINT_TARGET_POSITION);
	MelLib::Camera::Get()->SetRotateCriteriaPosition(MelLib::Vector3(0, 8, 0));
	

	bool res = MelLib::ModelData::Load("Resource/stage1_1/stage1_1.obj", false, "Stage");
	res = MelLib::Texture::Load("Resource/title.png", "title");
	MelLib::Texture::Load("Resource/operation.png", "operation");
	Player::LoadResource();
	BackGround::LoadResource();
	Goal::LoadResource();

	ClearStaging::LoadResource();

	MelLib::SceneManager::GetInstance()->SetStartScene(new Title());
}


void Game::Finalize()
{
	MelLib::Library::Finalize();//絶対に最後に書く
}


void Game::Update()
{
	MelLib::SceneManager::GetInstance()->Update();
	//MelLib::SceneEditer::GetInstance()->Update();
	//MelLib::SceneManager::GetInstance()->Update();
	//MelLib::SceneEditer::GetInstance()->Update();
	//MelLib::GameObjectManager::GetInstance()->Update();
  
	//player->Update();
	//for (std::unique_ptr<BaseEnemy>& enemyObj : enemy) {
	//	enemyObj->Update();
	//}
}

void Game::Draw()
{
	MelLib::SceneManager::GetInstance()->Draw();
	//MelLib::SceneEditer::GetInstance()->Draw();

	//MelLib::SceneManager::GetInstance()->Draw();
	//MelLib::SceneEditer::GetInstance()->Draw();

	//MelLib::GameObjectManager::GetInstance()->Draw();

	//player->Draw();
	//for (std::unique_ptr<BaseEnemy>& enemyObj : enemy) {
	//	enemyObj->Draw();
	//}
}