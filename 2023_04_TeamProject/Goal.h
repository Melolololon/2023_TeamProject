#pragma once
#include<GameObject.h>
class Goal :public MelLib::GameObject
{
public:
	static void LoadResource();

	// ���Ɉ����ō��W���w��
	Goal();

	void Initialize()override;

	std::shared_ptr<GameObject> GetNewPtr() override;
};

