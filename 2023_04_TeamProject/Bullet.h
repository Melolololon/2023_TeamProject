#pragma once
#include <GameObject.h>

using namespace MelLib;

class Bullet : public GameObject
{
public:
	static void LoadResource();

	Bullet();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	/// <summary>
	/// 弾を設定
	/// </summary>
	/// <param name="position">開始地点</param>
	/// <param name="rotation">飛ぶ方向</param>
	/// <param name="velocityMagnification">速度の倍率(初期値{ 0, 0, 1})</param>
	/// <param name="power">攻撃力</param>
	void SetParameter(Vector3 position, float rotation, float velocityMagnification = 1.0f, float power = 1.0f);

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
	const float PI = 3.141592;

public:
	// 座標
	Vector3 position{};
	// 速度
	Vector3 velocity = { 1.0f, 1.0f, 0.0f };
	// 攻撃力
	float power = 0.0f;
	// 開始フレーム
	int frame = 0;
	// 終了フレーム
	int end_frame = 100;
};

