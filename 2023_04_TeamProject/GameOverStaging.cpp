#include "GameOverStaging.h"

#include"Library.h"

void GameOverStaging::FrameMove()
{
	frameSpriteUp.SetPosition(frameSpriteUp.GetPosition() + MelLib::Vector2(0, 5.0f));
	frameSpriteDown.SetPosition(frameSpriteDown.GetPosition() - MelLib::Vector2(0, 5.0f));
}

void GameOverStaging::StringUpdate()
{
	const float SCALE_X = stringSprite.GetScale().x;
	if (SCALE_X > 1.0f)
	{
		stringSprite.SetScale(SCALE_X - 4.0f);
	}

	if (SCALE_X <= 1.0f)
	{
		stringSprite.SetScale(1.0f);
		sceneChangeTimer.SetStartFlag(true);
	}
}

void GameOverStaging::LoadResource()
{
	MelLib::Texture::Load("Resource/gameover/frame.png", "gameoverFrame");
	MelLib::Texture::Load("Resource/gameover/string.png", "gameoverString");
}

void GameOverStaging::Initialize()
{
	const float WIN_Y = MelLib::Library::GetWindowHeight();
	const float START_FRAME_POS_Y = 200;

	frameSpriteUp.Create(MelLib::Texture::Get("gameoverFrame"));
	frameSpriteUp.SetPosition({ 0,-START_FRAME_POS_Y });

	frameSpriteDown.Create(MelLib::Texture::Get("gameoverFrame"));
	frameSpriteDown.SetPosition({ 0,WIN_Y });

	stringSprite.Create(MelLib::Texture::Get("gameoverString"));
	stringSprite.SetPosition({ 270.0f,173.0f });
	stringSprite.SetScalingPoint(0.5f);
	stringSprite.SetScale(50);

	sceneChangeTimer.SetMaxTime(60 * 1.5f);
}

void GameOverStaging::Update()
{

	if (frameSpriteUp.GetPosition().y < 0)
	{
		FrameMove();
	}
	else
	{
		StringUpdate();
	}

}

void GameOverStaging::Draw()
{
	frameSpriteUp.Draw();
	frameSpriteDown.Draw();
	stringSprite.Draw();
}
