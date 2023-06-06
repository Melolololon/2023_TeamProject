#include "Bullet.h"
#include "Input.h"
#include"Stage.h"

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
	sphereDatas["main"][0].SetRadius(GetScale().x / 2);

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
}

void Bullet::Hit(const GameObject& object, const ShapeType3D shapeType, const std::string& shapeName, const ShapeType3D hitObjShapeType, const std::string& hitShapeName)
{
	Vector3 position = GetPosition();
	if (typeid(object) == typeid(Stage))
	{
		frame = end_frame;
	}
}
