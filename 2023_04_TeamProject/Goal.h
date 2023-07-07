#pragma once
#include<GameObject.h>
class Goal :public MelLib::GameObject
{
public:
	static void LoadResource();

	// ‰¼‚Éˆø”‚ÅÀ•W‚ğw’è
	Goal();

	void Initialize()override;

	std::shared_ptr<GameObject> GetNewPtr() override;
};

