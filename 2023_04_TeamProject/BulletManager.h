#pragma once
#include <forward_list>
#include "Bullet.h"

using namespace std;

class Bullet;

class BulletManager
{
public:
	static BulletManager* GetInstance();

	void Update();

	void Draw();

	/// <summary>
	/// 弾を発射
	/// </summary>
	/// <param name="position">開始地点</param>
	/// <param name="rotation">飛ぶ方向</param>
	/// <param name="velocityMagnification">速度の倍率(初期値{ 0, 0, 1})</param>
	/// <param name="power">攻撃力</param>
	void Fire(Vector3 position, float rotation, float velocityMagnification = 1.0f, float power = 1.0f);

	/// <summary>
	/// 弾を全て削除
	/// </summary>
	void AllClear();

private:
	std::forward_list<Bullet> bullets;
};

