#pragma once
#include<GameObject.h>
class Goal :public MelLib::GameObject
{
public:
	static void LoadResource();

	Goal();

	void Initialize()override;
};

