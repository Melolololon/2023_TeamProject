#pragma once
#include<GameObject.h>
class Goal :public MelLib::GameObject
{
public:
	static void LoadResource();

	// 仮に引数で座標を指定
	Goal();

	void Initialize()override;

	std::shared_ptr<GameObject> GetNewPtr() override;
};

