#pragma once
#include<GameObject.h>
class Goal :public MelLib::GameObject
{
public:
	static void LoadResource();

	// ‰¼‚Éˆø”‚ÅÀ•W‚ğw’è
	Goal(const MelLib::Vector3& pos);

	void Initialize()override;
};

