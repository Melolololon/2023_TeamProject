#pragma once
#include<Sprite2D.h>


// �X�N���[����z�肵�ăN���X��
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

