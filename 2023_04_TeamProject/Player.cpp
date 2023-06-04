#include "Player.h"
#include "BulletManager.h"

#include<GameObjectManager.h>
#include "Input.h"
#include "Library.h"
#define PI 3.141592

#include"Stage.h"

void Player::LoadResource()
{
	MelLib::ModelData::Load("Resource/player/player.fbx", false, "player");
}

Player::Player()
	:GameObject("Player")
{
	modelObjects["main"].Create(MelLib::ModelData::Get("player"), GetObjectName());

	// imgui
	power.SetData(1.0f, GetObjectName(), "JumpPower", 0.0f, 1.0f);
	speed.SetData(0.5f, GetObjectName(), "MoveSpeed", 0.0f, 1.0f);
	gravity.SetData(0.005f, "SceneParameter", "Gravity", 0.0f, 1.0f);

	SetScale({ 4,4,4 });

}

void Player::Initialize()
{
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(GetScale().x / 2);

	MelLib::Value2<MelLib::Vector3>segmentPos;
	float offset = 0.01f;
#pragma region ������

	segment3DDatas["ground"].resize(2);
	// �E��
	segmentPos.v1 = GetPosition() + MelLib::Vector3(+sphereDatas["main"][0].GetRadius() + offset, sphereDatas["main"][0].GetRadius(), 0);
	segmentPos.v2 = GetPosition() - MelLib::Vector3(+sphereDatas["main"][0].GetRadius() + offset, sphereDatas["main"][0].GetRadius(), 0);
	segment3DDatas["ground"][0].SetPosition(segmentPos);
	// ����
	segmentPos.v1 = GetPosition() + MelLib::Vector3(-sphereDatas["main"][0].GetRadius() - offset, sphereDatas["main"][0].GetRadius(), 0);
	segmentPos.v2 = GetPosition() - MelLib::Vector3(-sphereDatas["main"][0].GetRadius() - offset, sphereDatas["main"][0].GetRadius(), 0);
	segment3DDatas["ground"][1].SetPosition(segmentPos);

#pragma endregion

#pragma region �ǔ���

	segment3DDatas["wall"].resize(2);
	// �㑤
	segmentPos.v1 = GetPosition() + MelLib::Vector3(sphereDatas["main"][0].GetRadius(), +sphereDatas["main"][0].GetRadius() + offset, 0);
	segmentPos.v2 = GetPosition() - MelLib::Vector3(sphereDatas["main"][0].GetRadius(), +sphereDatas["main"][0].GetRadius() + offset, 0);
	segment3DDatas["wall"][0].SetPosition(segmentPos);
	// ����
	segmentPos.v1 = GetPosition() + MelLib::Vector3(sphereDatas["main"][0].GetRadius(), -sphereDatas["main"][0].GetRadius() - offset, 0);
	segmentPos.v2 = GetPosition() - MelLib::Vector3(sphereDatas["main"][0].GetRadius(), -sphereDatas["main"][0].GetRadius() - offset, 0);
	segment3DDatas["wall"][1].SetPosition(segmentPos);

#pragma endregion
	tags.push_back("Player");
	skipCollisionCheckTags.push_back("Bullet");
}

void Player::Update()
{
	GameObject::SetGravutationalAcceleration(gravity.GetValue());
	thisState = ThisState::STOP;

	Jump();
	Move();
	Shot();
	SetAnimation();
}

void Player::Draw()
{
	AllDraw();
}

std::shared_ptr<GameObject> Player::GetNewPtr()
{
	return std::make_shared<Player>();
}

void Player::Hit(const GameObject& object, const ShapeType3D shapeType, const std::string& shapeName, const ShapeType3D hitObjShapeType, const std::string& hitShapeName)
{
	Vector3 position = GetPosition();
	if (typeid(object) == typeid(Stage)
		&& shapeType == ShapeType3D::SEGMENT)
	{
		// ������
		if (GetHitTriangleData().GetNormal().y == 1.0f) 
		{
			FallEnd();

			Segment3DCalcResult result = GetSegmentCalcResult();
			
			const float ADD_Y = result.triangleHitPos.y - GetPosition().y + sphereDatas["main"][0].GetRadius();
			AddPosition(Vector3(0, ADD_Y,0));
			
			jumping = false;
		}
		else // �ǔ��� 
		{
			Segment3DCalcResult result = GetSegmentCalcResult();

			if (GetHitTriangleData().GetNormal().x == 1.0f)
			{
				const float ADD_X = result.triangleHitPos.x - GetPosition().x + sphereDatas["main"][0].GetRadius();
				AddPosition(Vector3(ADD_X, 0, 0));
			}
			else if (GetHitTriangleData().GetNormal().x == -1.0f)
			{
				const float ADD_X = result.triangleHitPos.x - GetPosition().x - sphereDatas["main"][0].GetRadius();
				AddPosition(Vector3(ADD_X, 0, 0));
			}
		}
	}
}

void Player::Move()
{
	Vector3 position = GetPosition();
	Vector3 cpos = Camera::Get()->GetCameraPosition();

	if (Input::KeyState(DIK_A) || Input::KeyState(DIK_D))
	{
		if (Input::KeyState(DIK_A))
		{
			position.x -= speed.GetValue();
		}
		else if (Input::KeyState(DIK_D))
		{
			position.x += speed.GetValue();
		}

		thisState = ThisState::DASH;
	}

	cpos = Vector3(position.x, position.y + 10, 0);
	Camera::Get()->SetRotateCriteriaPosition(cpos);

	SetPosition(position);
}

void Player::Jump()
{
	Vector3 position = GetPosition();

	if (Input::KeyTrigger(DIK_SPACE) && !jumping)
	{
		power.SetValue(0.5f);
		FallStart(power.GetValue());
		jumping = true;

		thisState = ThisState::JUMP;
	}

	if (!jumping)
	{
		power.SetValue(0.0f);
		FallStart(power.GetValue());
		jumping = true;
	}

	CalcMovePhysics();
}

void Player::Shot()
{
	isShot = false;

	Vector3 position = GetPosition();
	Vector2 mousevec = Input::GetMouseVector(mousecenter);
	float angle = -atan2f(mousevec.y, mousevec.x) * 180 / PI;

	if (Input::MouseButtonTrigger(MouseButton::LEFT))
	{
		std::shared_ptr<Bullet>b = std::make_shared<Bullet>();
		MelLib::GameObjectManager::GetInstance()->AddObject(b);
		b->SetParameter(position, angle);

		isShot = true;
	}
}

void Player::SetAnimation()
{
	std::string animName;
	switch (thisState)
	{
	case Player::ThisState::STOP:
		animName = "STOP";
		break;
	case Player::ThisState::DASH:
		animName = "DASH";
		break;
	case Player::ThisState::JUMP:
		animName = "MOVE";
		break;
	case Player::ThisState::DEAD:
		animName = "DEAD";
		break;
	default:
		break;
	}

	SetUpperBodyAnimation(animName);
}

void Player::SetUpperBodyAnimation(const std::string& animName)
{
	if (isShot) 
	{
	}
	else 
	{
	}
}
