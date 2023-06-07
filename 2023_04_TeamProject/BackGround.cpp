#include "BackGround.h"

void BackGround::LoadResource()
{
	MelLib::Texture::Load("Resource/back.png","BackGround");
}

BackGround::BackGround()
{
	sprite.Create(MelLib::Texture::Get("BackGround"));
	sprite.SetScale({ 1.2f,1.2f });
	
}

void BackGround::Update()
{
}

void BackGround::Draw()
{
	sprite.Draw();
}
