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
	/// �e�𔭎�
	/// </summary>
	/// <param name="position">�J�n�n�_</param>
	/// <param name="rotation">��ԕ���</param>
	/// <param name="velocityMagnification">���x�̔{��(�����l{ 0, 0, 1})</param>
	/// <param name="power">�U����</param>
	void Fire(Vector3 position, float rotation, float velocityMagnification = 1.0f, float power = 1.0f);

	/// <summary>
	/// �e��S�č폜
	/// </summary>
	void AllClear();

private:
	std::forward_list<Bullet> bullets;
};

