#include "Player.h"
#include "Input.h"

Player::Player()
	:GameObject("Player")
{
	modelObjects["main"].Create(MelLib::ModelData::Get(ShapeType3D::BOX), GetObjectName());

	power.SetData(0.5f, GetObjectName(), "JumpPower", 0.0f, 1.0f);
	speed.SetData(0.5f, GetObjectName(), "MoveSpeed", 0.0f, 1.0f);
}

void Player::Initialize()
{
}

void Player::Update()
{
	Vector3 position = GetPosition();

	if (Input::KeyState(DIK_A) || Input::KeyState(DIK_D))
	{
		if (Input::KeyState(DIK_A)) position.x -= speed.GetValue();
		else if (Input::KeyState(DIK_D)) position.x += speed.GetValue();

		SetPosition(position);
	}

	if (Input::KeyTrigger(DIK_SPACE))
	{
		FallStart(power.GetValue());
	}

	CalcMovePhysics();

	if (position.y < 0)
	{
		FallEnd();

		position.y = 0;
		SetPosition(position);
	}
}

void Player::Draw()
{
	AllDraw();
}
