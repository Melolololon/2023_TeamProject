#include "CursorTexture.h"

#include<Input.h>

CursorTexture::CursorTexture()
{
	sprite.Create(MelLib::Color(255, 0, 0, 255));
	sprite.SetScale(60);

	MelLib::Input::SetDrawCursorFlag(false);
}

CursorTexture::~CursorTexture()
{
	MelLib::Input::SetDrawCursorFlag(true);
}


void CursorTexture::Update()
{
	MelLib::Input::SetDrawCursorFlag(false);
	const MelLib::Vector2 TEX_SIZE_HALF = 30;
	sprite.SetPosition(MelLib::Input::GetMousePosition() - TEX_SIZE_HALF);
	
}

void CursorTexture::Draw()
{
	sprite.Draw();
}
