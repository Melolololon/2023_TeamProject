#include "Player.h"
#include "BulletManager.h"
#include "Input.h"

Player::Player()
	:GameObject("Player")
{
	modelObjects["main"].Create(MelLib::ModelData::Get(ShapeType3D::BOX), GetObjectName());

	power.SetData(0.5f, GetObjectName(), "JumpPower", 0.0f, 1.0f);
	speed.SetData(0.5f, GetObjectName(), "MoveSpeed", 0.0f, 1.0f);
	gravity.SetData(0.5f, "SceneParameter", "Gravity", 0.0f, 1.0f);
}

void Player::Initialize()
{
	Vector3 position = GetPosition();
}

void Player::Update()
{
	GameObject::SetGravutationalAcceleration(gravity.GetValue());

	Move();
	Jump();
	Shot();
}

void Player::Draw()
{
	AllDraw();
	BulletManager::GetInstance()->Draw();
}

void Player::Move()
{
	Vector3 position = GetPosition();

	if (Input::KeyState(DIK_A) || Input::KeyState(DIK_D))
	{
		if (Input::KeyState(DIK_A)) position.x -= speed.GetValue();
		else if (Input::KeyState(DIK_D)) position.x += speed.GetValue();

		SetPosition(position);
	}
}

void Player::Jump()
{
	Vector3 position = GetPosition();

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

void Player::Shot()
{
	Vector3 position = GetPosition();

	if (Input::MouseButtonTrigger(MouseButton::LEFT))
	{
		BulletManager::GetInstance()->Fire(position, 0);
	}

	BulletManager::GetInstance()->Update();
}
