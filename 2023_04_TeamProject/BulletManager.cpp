#include "BulletManager.h"
#include "GameObjectManager.h"

BulletManager* BulletManager::GetInstance()
{
	static BulletManager instance;
	return &instance;
}

void BulletManager::Initialize()
{
	for (auto& bullet : bullets) 
	{
		bullet = std::make_shared<Bullet>();
		GameObjectManager::GetInstance()->AddObject(bullet);
	}
}


void BulletManager::Update()
{
	// éıñΩÇ™êsÇ´ÇΩíeÇëSçÌèú
	ordBullets.remove_if([](Bullet& x) { return x.frame >= x.end_frame; });

	// ëSíeçXêV
	for (std::forward_list<Bullet>::iterator it = ordBullets.begin();
		it != ordBullets.end(); it++)
	{
		it->frame++;
		it->position = it->position + it->velocity;
		it->Update();
	}
}

void BulletManager::Draw()
{
	for (auto& bullet : ordBullets)
	{
		bullet.Draw();
	}
}

void BulletManager::Fire(Vector3 position, float rotation, float velocityMagnification, float power)
{
	// í«â¡ÇµÇΩóvëfÇÃéQè∆
	GameObjectManager::GetInstance()->AddObject(std::make_shared<Bullet>());
}

void BulletManager::AllClear()
{
}
