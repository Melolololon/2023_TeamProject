#pragma once
#include <GameObject.h>

#include<GuiValue.h>
#include "Bullet.h"

using namespace MelLib;

class Player : public GameObject
{
	GuiFloat power;
	GuiFloat speed;
	GuiFloat gravity;

public:
	Player();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	// ポインター
	// エディタで配置するのに使う
	std::shared_ptr<GameObject> GetNewPtr() override;

	/// <summary>
	/// 衝突した時に呼び出される判定
	/// </summary>
	/// <param name="object">オブジェクト</param>
	/// <param name="shapeType">自分のどの形状の判定と当たったか</param>
	/// <param name="shapeName">判定名</param>
	/// <param name="hitObjShapeType">相手の形状</param>
	/// <param name="hitShapeName">相手の判定名</param>
	void Hit
	(
		const GameObject& object,
		const ShapeType3D shapeType,
		const std::string& shapeName,
		const ShapeType3D hitObjShapeType,
		const std::string& hitShapeName
	) override;

private:

	// 移動
	void Move();
	// ジャンプ
	void Jump();
	// 射撃
	void Shot();

private:

	Vector2 mousecenter = Vector2(Library::GetWindowWidth() / 2.0f, 640.0);
};

