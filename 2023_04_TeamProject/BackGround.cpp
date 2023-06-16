#include "BackGround.h"
#include<Input.h>

void BackGround::LoadResource()
{
	MelLib::Texture::Load("Resource/back.png","BackGround");
}

BackGround::BackGround(const Player* const p)
	:pPlayer(p)
{
	sprite.Create(MelLib::Texture::Get("BackGround"));
	sprite.SetScale({ 1.2f,1.2f });
	sprite.SetDrawRigthDownPosition({ 5,1 });
	sprite.SetPosition({ -300,0 });
}

void BackGround::Update()
{
	if (pPlayer->GetHitWall())return;

	const float MOVE_SPEED = 0.6f;
	if (MelLib::Input::KeyState(DIK_A)) 
	{
		sprite.SetPosition(sprite.GetPosition() + MelLib::Vector2(MOVE_SPEED, 0));
	}
	else if (MelLib::Input::KeyState(DIK_D))
	{
		sprite.SetPosition(sprite.GetPosition() - MelLib::Vector2(MOVE_SPEED, 0));
	}
}

void BackGround::Draw()
{
	sprite.Draw();
}

