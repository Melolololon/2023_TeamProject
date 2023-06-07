#pragma once
#include <GameObject.h>

#include<FrameTimer.h>
#include<GuiValue.h>

#include "Bullet.h"
#include "Gauge.h"

using namespace MelLib;

class Player : public GameObject
{
	GuiFloat power;
	GuiFloat speed;
	GuiFloat gravity;


#pragma region 市川追加列挙
	// アニメーション制御用
	enum class ThisState 
	{
		STOP,
		DASH,
		JUMP,
		DEAD,
		FALL_DEAD,
		CLEAR
	};
#pragma endregion

public:
	static void LoadResource();

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

#pragma region 市川追加関数
	bool GetClear()const;
	bool GetDead()const;
#pragma endregion


private:

	// 移動
	void Move();
	// ジャンプ
	void Jump();
	// 射撃
	void Shot();

#pragma region 市川追加関数
	
	// 落下死確認
	void CheckFallDead();

	/// <summary>
	/// 移動による回転
	/// </summary>
	/// <param name="rotLeft">左かどうか。falseだと右。</param>
	void MoveRot();

	// アニメーション
	void Animation();

	/// <summary>
	/// 腕のアニメーション設定
	/// </summary>
	/// <param name="animName">セットするアニメーション名</param>
	void SetArmAnimation(const std::string& animName);

	/// <summary>
	/// ダッシュアニメーションによるY軸座標の加算処理
	/// </summary>
	void DashAnimationAddPosition();

	// アニメーションデータのセット
	void SetAnimationData();
	void SetArmAnimationData();
	// 腕アニメのリセと
	void ResetArmAnimationData();

	// ゴールした時
	void Clear();
#pragma endregion

private:

	Vector2 mousecenter = Vector2(Library::GetWindowWidth() / 2.0f, 750.0);

	// 弾
	static const int BULLET_MAX = 20;
	//std::array<std::shared_ptr<Bullet>, BULLET_MAX>bullets;
	Bullet bullets[BULLET_MAX]{};

	// ジャンプ中

	// HP
	static const int HPMax = 6;
	int HP = HPMax;

	// HPゲージ
	//Gauge HPGauge{};
	Sprite2D HPsprite[HPMax];

#pragma region 市川追加変数

	const MelLib::Vector3 START_ANGLE = MelLib::Vector3(0, 0, 0);
	const MelLib::Vector3 DEFORT_ANGLE = MelLib::Vector3(0, -90, 0);

	// ショットアニメーションを割り当てるボーン
	const std::vector<std::string> SET_SHOT_ANIM_BONE =
	{
		"R_Arm_1",
		"R_Arm_2",
		"R_Arm_3",
		"L_Arm_1",
		"L_Arm_2",
		"L_Arm_3",
		"Head",
	};

	// 自身の状態
	ThisState thisState = ThisState::STOP;

	// ショット中かどうか
	// ショットと移動などのその他行動が混ざるので、個別にフラグを用意
	bool isShotAnimation = false;

	// ショットアニメーションをショット終了から何秒後に終わるかセットし、カウントするタイマー
	MelLib::FrameTimer shotAnimEndTimer;

	bool playerDirLeft = false;

	bool hitGround = false;
	bool setGoalAnimData = false;

	MelLib::Value2<MelLib::Vector3> resetGroundSegmentPos[2];
#pragma endregion
};

