#pragma once
#include<Sprite2D.h>

// �N���A���o
class ClearStaging
{
private:
	MelLib::Sprite2D frameSpriteUp;
	MelLib::Sprite2D frameSpriteDown;
	MelLib::Sprite2D stringSprite;
public:
	static void LoadResource();

	void Initialize();
	void Update();
	void Draw();

};

