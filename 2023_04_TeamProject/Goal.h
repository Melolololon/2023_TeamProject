#pragma once
#include<GameObject.h>
class Goal :public MelLib::GameObject
{
public:
	static void LoadResource();

	// ���Ɉ����ō��W���w��
	Goal(const MelLib::Vector3& pos);

	void Initialize()override;
};

