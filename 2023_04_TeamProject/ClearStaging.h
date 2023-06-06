#pragma once
#include<Sprite2D.h>
#include<FrameTimer.h>

// ÉNÉäÉAââèo
class ClearStaging
{
private:
	MelLib::Sprite2D frameSpriteUp;
	MelLib::Sprite2D frameSpriteDown;
	MelLib::Sprite2D stringSprite;

	MelLib::FrameTimer sceneChangeTimer;

private:
	void FrameMove();
	void StringUpdate();


public:
	static void LoadResource();

	void Initialize();
	void Update();
	void Draw();

	bool GetSceneChangeFlag()const { return sceneChangeTimer.GetMaxOverFlag(); }
};

