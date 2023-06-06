#include "ClearStaging.h"

void ClearStaging::LoadResource()
{
	MelLib::Texture::Load("Resource/clear/frame.png", "clearFrame");
	MelLib::Texture::Load("Resource/clear/string.png", "clearString");
}

void ClearStaging::Initialize()
{
	frameSpriteUp.Create(MelLib::Texture::Get("clearFrame"));
	frameSpriteDown.Create(MelLib::Texture::Get("clearFrame"));
	stringSprite.Create(MelLib::Texture::Get("clearString"));
}

void ClearStaging::Update()
{
	
}

void ClearStaging::Draw()
{
	frameSpriteUp.Draw();
	frameSpriteDown.Draw();
	stringSprite.Draw();
}
