#include "BulletManager.h"
#define PI 3.141592

BulletManager* BulletManager::GetInstance()
{
	static BulletManager instance;
	return &instance;
}

void BulletManager::Update()
{
	// �������s�����e��S�폜
	bullets.remove_if([](Bullet& x) { return x.frame >= x.end_frame; });

	// �S�e�X�V
	for (std::forward_list<Bullet>::iterator it = bullets.begin();
		it != bullets.end(); it++)
	{
		it->frame++;
		it->position = it->position + it->velocity;
		it->Update();
	}
}

void BulletManager::Draw()
{
	for (auto& bullet : bullets)
	{
		bullet.Draw();
	}
}

void BulletManager::Fire(Vector3 position, float rotation, float velocityMagnification, float power)
{
	// ���X�g�ɗv�f��ǉ�
	bullets.emplace_front();
	// �ǉ������v�f�̎Q��
	Bullet& bullet = bullets.front();
	bullet.position = position;
	// �p�x���瑬�x�̃x�N�g�����v�Z
	bullet.velocity.x = bullet.velocity.x * cosf(rotation * (PI / 180));
	bullet.velocity.y = bullet.velocity.y * sinf(rotation * (PI / 180));
	bullet.velocity *= velocityMagnification;

	bullet.power = power;
}

void BulletManager::AllClear()
{
	bullets.clear();
}
