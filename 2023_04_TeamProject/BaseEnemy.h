#pragma once
#include "GameObject.h"
#include "Player.h"

using namespace MelLib;

class BaseEnemy:public GameObject
{
public:
	static std::unique_ptr<BaseEnemy> Create(const std::string& name, Player* player);
public:
	BaseEnemy(const std::string& name);
	~BaseEnemy();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Move();

	void SetPlayer(Player* player) { this->player = player; }
	Player* GetPlayer() { return player; }
private:
	Player* player;
	float moveX;
	float moveY;
	float moveAmount = 0.01f;
};

