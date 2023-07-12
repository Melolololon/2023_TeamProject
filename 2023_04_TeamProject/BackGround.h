#pragma once
#include<Sprite2D.h>

#include"Player.h"

// スクロールを想定してクラス化
class BackGround
{
private:
	MelLib::Sprite2D sprite;
	const Player* const pPlayer = nullptr;


public:
	static void LoadResource();

	BackGround(const Player* const p);
	void Update();
	void Draw();

};

