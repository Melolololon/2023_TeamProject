#pragma once
#include "GameObject.h"

using namespace MelLib;

class BaseEnemy:public GameObject
{
public:
	BaseEnemy(const std::string& name);
	~BaseEnemy();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
};

