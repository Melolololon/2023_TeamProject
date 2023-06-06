#include "ClearStaging.h"

#include"Library.h"

void ClearStaging::FrameMove()
{
	frameSpriteUp.SetPosition(frameSpriteUp.GetPosition() + MelLib::Vector2(0, 5.0f));
	frameSpriteDown.SetPosition(frameSpriteDown.GetPosition() - MelLib::Vector2(0, 5.0f));
}

void ClearStaging::StringUpdate()
{
	const float SCALE_X = stringSprite.GetScale().x;
	if (SCALE_X > 1.0f)
	{
		stringSprite.SetScale(SCALE_X - 4.0f);
	}
	
	if (SCALE_X <= 1.0f)
	{
		stringSprite.SetScale(1.0f);
	}
}

void ClearStaging::LoadResource()
{
	MelLib::Texture::Load("Resource/clear/frame.png", "clearFrame");
	MelLib::Texture::Load("Resource/clear/string.png", "clearString");
}

void ClearStaging::Initialize()
{
	const float WIN_Y = MelLib::Library::GetWindowHeight();
	const float START_FRAME_POS_Y = 200;

	frameSpriteUp.Create(MelLib::Texture::Get("clearFrame"));
	frameSpriteUp.SetPosition({ 0,-START_FRAME_POS_Y});

	frameSpriteDown.Create(MelLib::Texture::Get("clearFrame"));
	frameSpriteDown.SetPosition({ 0,WIN_Y});
	
	stringSprite.Create(MelLib::Texture::Get("clearString"));
	stringSprite.SetPosition({ 270.0f,164.0f });
	stringSprite.SetScalingPoint(0.5f);
	stringSprite.SetScale(50);
}

void ClearStaging::Update()
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

void ClearStaging::Draw()
{
	frameSpriteUp.Draw();
	frameSpriteDown.Draw();
	stringSprite.Draw();
}
