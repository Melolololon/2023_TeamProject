#pragma once
#include<Sprite2D.h>

// è∆èÄ
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

