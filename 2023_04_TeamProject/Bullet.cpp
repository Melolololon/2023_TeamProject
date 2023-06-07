#include "Bullet.h"
#include "Input.h"
#include"Stage.h"

#include<LibMath.h>

void Bullet::LoadResource()
{
	MelLib::ModelData::Load("Resource/playerBullet/playerBullet.obj", false, "PlayerBullet");
}

Bullet::Bullet()
	:GameObject("Bullet")
{
	modelObjects["main"].Create(MelLib::ModelData::Get("PlayerBullet"), GetObjectName());
}

void Bullet::Initialize()
{
	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(2);

	collisionCheckDistance = sphereDatas["main"][0].GetRadius();
	tags.push_back("Bullet");
	skipCollisionCheckTags.push_back("Player");

}

void Bullet::Update()
{
	if (frame >= end_frame)
	{
		eraseManager = true;
		return;
	}

	frame++;
	position = position + velocity;
	SetPosition(position);
}

void Bullet::Draw()
{
	if (frame >= end_frame) return;

	AllDraw();
}

void Bullet::SetParameter(Vector3 position, float rotation, float velocityMagnification, float power)
{
	this->position = position;
	// 角度から速度のベクトルを計算
	velocity.x = velocity.x * cosf(rotation * (PI / 180));
	velocity.y = velocity.y * sinf(rotation * (PI / 180));
	velocity *= velocityMagnification;
	this->power = power;

	// 角度を指定
	// velocityが0,0で左を向くようにするために90をセット
	MelLib::Vector3 angle(0,0,90);

	const float CALC_ANGLE = MelLib::LibMath::Vector2ToAngle({ velocity.x,velocity.y }, true);
	angle.z += CALC_ANGLE;

	SetAngle(angle);
}

void Bullet::Hit(const GameObject& object, const ShapeType3D shapeType, const std::string& shapeName, const ShapeType3D hitObjShapeType, const std::string& hitShapeName)
{
	Vector3 position = GetPosition();
	if (typeid(object) == typeid(Stage))
	{
		frame = end_frame;
	}
}
