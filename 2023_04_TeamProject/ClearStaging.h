#pragma once
#include<Sprite2D.h>

// ÉNÉäÉAââèo
class ClearStaging
{
private:
	MelLib::Sprite2D frameSpriteUp;
	MelLib::Sprite2D frameSpriteDown;
	MelLib::Sprite2D stringSprite;

private:
	void FrameMove();
	void StringUpdate();


public:
	static void LoadResource();

	void Initialize();
	void Update();
	void Draw();

};

