#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "BaseEnemy.h"
#include "Stage.h"
#include"Goal.h"

#include"Fade.h"

#include"ClearStaging.h"
#include"GameOverStaging.h"

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
#include"Dorakiti.h"

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


	MelLib::Library::Initialize(1920, 1080, MelLib::Color(0, 0, 255, 255), L"洞窟");
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

	const bool EDITER_FLAG = false;

	MelLib::ImguiManager::GetInstance()->SetReleaseDrawFlag(EDITER_FLAG);
	MelLib::SceneEditer::GetInstance()->SetEditerFlag(EDITER_FLAG);
	MelLib::SceneEditer::GetInstance()->SetReleaseEditFlag(EDITER_FLAG);
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


	MelLib::Texture::Load("Resource/magic circle/magic circle1.png", "cursorTex");
	bool res = MelLib::ModelData::Load("Resource/stage/stage.obj", false, "Stage1");
	res = MelLib::ModelData::Load("Resource/stage2/stage2.obj", false, "Stage2");
	res = MelLib::ModelData::Load("Resource/dorakiti/dorakiti.obj", false, "Dorakiti");
	res = MelLib::ModelData::Load("Resource/surakiti/surakiti.obj", false, "surakiti");
	res = MelLib::Texture::Load("Resource/title.png", "title");
	MelLib::Texture::Load("Resource/operation.png", "operation");
	MelLib::Texture::Load("Resource/hp.png", "hp");
	Player::LoadResource();
	Bullet::LoadResource();
	BackGround::LoadResource();
	Goal::LoadResource();

	ClearStaging::LoadResource();
	GameOverStaging::LoadResource();

	Fade::GetInstance()->Initializ();


	MelLib::SceneEditer::GetInstance()->RegisterObject(std::make_shared<BaseEnemy>("surakiti"),"Enemy");
	MelLib::SceneEditer::GetInstance()->RegisterObject(std::make_shared<Dorakiti>("Dorakiti"),"Enemy");
	MelLib::SceneEditer::GetInstance()->RegisterObject(std::make_shared<Player>(),"Player");
	MelLib::SceneEditer::GetInstance()->RegisterObject(std::make_shared<Goal>(),"Stage");
	MelLib::SceneEditer::GetInstance()->RegisterObject(std::make_shared<Stage>(1),"Stage");
	MelLib::SceneEditer::GetInstance()->RegisterObject(std::make_shared<Stage>(2),"Stage");

	MelLib::SceneManager::GetInstance()->SetStartScene(new Play());
}


void Game::Finalize()
{
	MelLib::Library::Finalize();//絶対に最後に書く
}


void Game::Update()
{
	MelLib::SceneManager::GetInstance()->Update();
	MelLib::SceneEditer::GetInstance()->Update();
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
	MelLib::SceneEditer::GetInstance()->Draw();

	//MelLib::SceneManager::GetInstance()->Draw();
	//MelLib::SceneEditer::GetInstance()->Draw();

	//MelLib::GameObjectManager::GetInstance()->Draw();

	//player->Draw();
	//for (std::unique_ptr<BaseEnemy>& enemyObj : enemy) {
	//	enemyObj->Draw();
	//}
}