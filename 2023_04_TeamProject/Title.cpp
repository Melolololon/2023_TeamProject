#include "Title.h"

#include"Play.h"
#include"Fade.h"

#include<Input.h>

void Title::Initialize()
{
	titleSprite.Create(MelLib::Texture::Get("title"));
}

void Title::Update()
{
	if (MelLib::Input::KeyTrigger(DIK_SPACE)) 
	{
		Fade::GetInstance()->Start();
	}


	Fade::GetInstance()->Update();
	if (Fade::GetInstance()->GetChangeSceneFlag())
	{
		isEnd = true;
	}

}

void Title::Draw()
{
	titleSprite.Draw();
	Fade::GetInstance()->Draw();
}

void Title::Finalize()
{
}

MelLib::Scene* Title::GetNextScene()
{
	return new Play;
}
