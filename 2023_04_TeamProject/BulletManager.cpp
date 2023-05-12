#include "BulletManager.h"
#define PI 3.141592

BulletManager* BulletManager::GetInstance()
{
	static BulletManager instance;
	return &instance;
}

void BulletManager::Update()
{
	// 寿命が尽きた弾を全削除
	bullets.remove_if([](Bullet& x) { return x.frame >= x.end_frame; });

	// 全弾更新
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
	// リストに要素を追加
	bullets.emplace_front();
	// 追加した要素の参照
	Bullet& bullet = bullets.front();
	bullet.position = position;
	// 角度から速度のベクトルを計算
	bullet.velocity.x = bullet.velocity.x * cosf(rotation * (PI / 180));
	bullet.velocity.y = bullet.velocity.y * sinf(rotation * (PI / 180));
	bullet.velocity *= velocityMagnification;

	bullet.power = power;
}

void BulletManager::AllClear()
{
	bullets.clear();
}
