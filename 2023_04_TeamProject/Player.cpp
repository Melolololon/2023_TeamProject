#include "Player.h"
#include "BulletManager.h"

#include<GameObjectManager.h>
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
	gravity.SetData(0.005f, "SceneParameter", "Gravity", 0.0f, 1.0f);

	SetScale({ 4,4,4 });

	for (int i = 0; i < HPMax; i++)
	{
		HPsprite[i].Create(Color(255, 200, 200, 255));
		HPsprite[i].SetScale({ 10, 10 });

		float offset = (HPsprite[i].GetScale().x * HPsprite[i].GetScale().y + 50) * i;
		HPsprite[i].SetPosition({ 100 + offset, 100 });
	}
}

void Player::Initialize()
{
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(GetScale().x / 2);

	MelLib::Value2<MelLib::Vector3>segmentPos;
	float offset = -0.01f;
#pragma region è∞îªíË

	segment3DDatas["ground"].resize(2);
	// âEë§
	segmentPos.v1 = GetPosition() + MelLib::Vector3(+sphereDatas["main"][0].GetRadius() + offset, sphereDatas["main"][0].GetRadius(), 0);
	segmentPos.v2 = GetPosition() - MelLib::Vector3(+sphereDatas["main"][0].GetRadius() + offset, sphereDatas["main"][0].GetRadius(), 0);
	segment3DDatas["ground"][0].SetPosition(segmentPos);
	// ç∂ë§
	segmentPos.v1 = GetPosition() + MelLib::Vector3(-sphereDatas["main"][0].GetRadius() - offset, sphereDatas["main"][0].GetRadius(), 0);
	segmentPos.v2 = GetPosition() - MelLib::Vector3(-sphereDatas["main"][0].GetRadius() - offset, sphereDatas["main"][0].GetRadius(), 0);
	segment3DDatas["ground"][1].SetPosition(segmentPos);
#pragma endregion


#pragma region ï«îªíË

	segment3DDatas["wall"].resize(2);
	// è„ë§
	segmentPos.v1 = GetPosition() + MelLib::Vector3(sphereDatas["main"][0].GetRadius(), +sphereDatas["main"][0].GetRadius() + offset, 0);
	segmentPos.v2 = GetPosition() - MelLib::Vector3(sphereDatas["main"][0].GetRadius(), +sphereDatas["main"][0].GetRadius() + offset, 0);
	segment3DDatas["wall"][0].SetPosition(segmentPos);
	// â∫ë§
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

	Jump();
	Move();
	Shot();

	if(Input::KeyTrigger(DIK_0)) HP--;
}

void Player::Draw()
{
	AllDraw();

	for (int i = 0; i < HP; i++)
	{
		HPsprite[i].Draw();
	}
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
		// è∞îªíË
		if (GetHitTriangleData().GetNormal().y == 1.0f && shapeName == "ground")
		{
			FallEnd();

			Segment3DCalcResult result = GetSegmentCalcResult();
			
			const float ADD_Y = result.triangleHitPos.y - GetPosition().y + sphereDatas["main"][0].GetRadius();
			AddPosition(Vector3(0, ADD_Y,0));
			
			jump = ON_GROUND;
		}
		if(shapeName == "wall") // ï«îªíË 
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
	}

	cpos = Vector3(position.x, position.y + 10, 0);
	Camera::Get()->SetRotateCriteriaPosition(cpos);

	SetPosition(position);
}

void Player::Jump()
{
	Vector3 position = GetPosition();

	if (Input::KeyTrigger(DIK_SPACE) && jump == ON_GROUND)
	{
		power.SetValue(0.5f);
		FallStart(power.GetValue());
		jump = JUMPING;
	}
	if (jump == ON_GROUND)
	{
		jump = STAY_IN_AIR;
	}
	if (jump == STAY_IN_AIR)
	{
		power.SetValue(0.0f);
		FallStart(power.GetValue());
		jump = FALLING;
	}

	CalcMovePhysics();
}

void Player::Shot()
{
	Vector3 position = GetPosition();
	Vector2 mousevec = Input::GetMouseVector(mousecenter);
	float angle = -atan2f(mousevec.y, mousevec.x) * 180 / PI;

	if (Input::MouseButtonTrigger(MouseButton::LEFT))
	{
		std::shared_ptr<Bullet>b = std::make_shared<Bullet>();
		MelLib::GameObjectManager::GetInstance()->AddObject(b);
		b->SetParameter(position, angle);
	}
}
