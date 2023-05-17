#include "Bullet.h"
#include "Input.h"

Bullet::Bullet()
	:GameObject("Bullet")
{
	modelObjects["main"].Create(MelLib::ModelData::Get(ShapeType3D::BOX), GetObjectName());
}

void Bullet::Initialize()
{

}

void Bullet::Update()
{
	SetPosition(position);
}

void Bullet::Draw()
{
	AllDraw();
}
