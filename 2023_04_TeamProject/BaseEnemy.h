#pragma once
#include "GameObject.h"
#include "Player.h"

using namespace MelLib;

class BaseEnemy:public GameObject
{
public:
	static std::shared_ptr<BaseEnemy> Create(const std::string& name, Player* player);

	
public:
	BaseEnemy(const std::string& name);
	~BaseEnemy();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	virtual void Move();

	void Hit
	(
		const GameObject& object,
		const ShapeType3D shapeType,
		const std::string& shapeName,
		const ShapeType3D hitObjShapeType,
		const std::string& hitShapeName
	) override;

	void Damage();

	static void SetPlayer(Player* p) { player = p; }
	Player* GetPlayer() { return player; }

	std::shared_ptr<GameObject> GetNewPtr() override;
protected:
	static Player* player;
	//Player* player = nullptr;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float moveAmount = 0.1f;
};

