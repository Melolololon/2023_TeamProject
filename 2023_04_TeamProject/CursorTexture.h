#pragma once
#include<Sprite2D.h>

// �Ə�
class CursorTexture
{
private:

	MelLib::Sprite2D sprite;

public:
	CursorTexture();
	~CursorTexture();

	void Update();
	void Draw();

};

