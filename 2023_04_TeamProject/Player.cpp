#include "Player.h"
#include "BulletManager.h"
#include "Input.h"
#include "Library.h"
#define PI 3.141592

#include"Stage.h"

Player::Player()
	:GameObject("Player")
{
	modelObjects["main"].Create(MelLib::ModelData::Get(ShapeType3D::BOX), GetObjectName());

	// imgui
	power.SetData(1.0f, GetObjectName(), "JumpPower", 0.0f, 1.0f);
	speed.SetData(0.5f, GetObjectName(), "MoveSpeed", 0.0f, 1.0f);
	gravity.SetData(0.1f, "SceneParameter", "Gravity", 0.0f, 1.0f);

	SetScale({ 4,4,4 });

}

void Player::Initialize()
{
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(GetScale().x / 2);

	segment3DDatas["main"].resize(1);
	MelLib::Value2<MelLib::Vector3>segmentPos;
	segmentPos.v1 = GetPosition() + MelLib::Vector3(sphereDatas["main"][0].GetRadius());
	segmentPos.v2 = GetPosition() - MelLib::Vector3(sphereDatas["main"][0].GetRadius());
	segment3DDatas["main"][0].SetPosition(segmentPos);
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
	// ’e‚Ì•`‰æ
	BulletManager::GetInstance()->Draw();
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
		// °”»’è
		if (GetHitTriangleData().GetNormal().y == 1.0f) 
		{
			FallEnd();

			/*position.y = 0;
			SetPosition(position);*/

			Segment3DCalcResult result = GetSegmentCalcResult();
			
			const float ADD_Y = result.triangleHitPos.y - GetPosition().y + sphereDatas["main"][0].GetRadius();
			AddPosition(Vector3(0, ADD_Y + 0.1f,0));
			
		}
		else // •Ç”»’è 
		{
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
			cpos.x -= speed.GetValue();
		}
		else if (Input::KeyState(DIK_D))
		{
			position.x += speed.GetValue();
			cpos.x += speed.GetValue();
		}

		cpos.z += Camera::Get()->GetCameraToTargetDistance();
		Camera::Get()->SetRotateCriteriaPosition(cpos);

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

	/*if (position.y < 0)
	{
		FallEnd();

		position.y = 0;
		SetPosition(position);
	}*/
}

void Player::Shot()
{
	Vector3 position = GetPosition();
	Vector2 mousevec = Input::GetMouseVector(mousecenter);
	float angle = -atan2f(mousevec.y, mousevec.x) * 180 / PI;

	if (Input::MouseButtonTrigger(MouseButton::LEFT))
	{
		BulletManager::GetInstance()->Fire(position, angle);
	}

	BulletManager::GetInstance()->Update();
}
