#include "Title.h"

#include"Play.h"

#include<Input.h>

void Title::Initialize()
{
	titleSprite.Create(MelLib::Texture::Get("title"));
}

void Title::Update()
{
	if (MelLib::Input::KeyTrigger(DIK_SPACE)) 
	{
		isEnd = true;
	}
}

void Title::Draw()
{
	titleSprite.Draw();
}

void Title::Finalize()
{
}

MelLib::Scene* Title::GetNextScene()
{
	return new Play;
}
