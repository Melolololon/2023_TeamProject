#include "BackGround.h"
#include<Input.h>

void BackGround::LoadResource()
{
	MelLib::Texture::Load("Resource/back.png","BackGround");
}

BackGround::BackGround()
{
	sprite.Create(MelLib::Texture::Get("BackGround"));
	sprite.SetScale({ 1.2f,1.2f });
	sprite.SetDrawRigthDownPosition({ 1.1,1 });
}

void BackGround::Update()
{
	if (MelLib::Input::KeyState(DIK_A)) 
	{
		sprite.SetPosition(sprite.GetPosition() + MelLib::Vector2(-3, 0));
	}
	else if (MelLib::Input::KeyState(DIK_D)) 
	{
		sprite.SetPosition(sprite.GetPosition() + MelLib::Vector2(3, 0));
	}
}

void BackGround::Draw()
{
	sprite.Draw();
}
