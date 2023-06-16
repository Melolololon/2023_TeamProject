#pragma once
#include<Sprite2D.h>

#include"Player.h"

// �X�N���[����z�肵�ăN���X��
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

