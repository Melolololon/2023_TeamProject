#pragma once
#include<Sprite2D.h>


// スクロールを想定してクラス化
class BackGround
{
private:
	MelLib::Sprite2D sprite;
public:
	static void LoadResource();

	BackGround();
	void Update();
	void Draw();
};

