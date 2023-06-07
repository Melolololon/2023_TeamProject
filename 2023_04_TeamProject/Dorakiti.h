#pragma once
#include "BaseEnemy.h"
#include "Easing.h"

class Dorakiti : public BaseEnemy
{
public:
	static std::shared_ptr<Dorakiti> Create(const std::string& name, Player* player);
public:
	Dorakiti(const std::string& name);

	void Move() override;
private:
	MelLib::Easing<float> easing;
};

