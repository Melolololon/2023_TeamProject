#include "Player.h"
#include "BulletManager.h"

#include"BaseEnemy.h"
#include"Dorakiti.h"

#include<GameObjectManager.h>
#include<Sound.h>

#include "Input.h"
#include "Library.h"
#define PI 3.141592

#include"Stage.h"
#include"Goal.h"

void Player::LoadResource()
{
	MelLib::ModelData::Load("Resource/player/player.fbx", false, "player");

	//MelLib::SoundData::Load();
}

Player::Player()
	:GameObject("Player")
{
	modelObjects["main"].Create(MelLib::ModelData::Get("player"), GetObjectName());

	// imgui
	power.SetData(1.0f, GetObjectName(), "JumpPower", 0.0f, 1.0f);
	speed.SetData(0.5f, GetObjectName(), "MoveSpeed", 0.0f, 1.0f);
	gravity.SetData(0.005f, "SceneParameter", "Gravity", 0.0f, 1.0f);

	SetScale({ 4,4,4 });

	for (int i = 0; i < HPMax; i++)
	{
		HPsprite[i].Create(Color(255, 200, 200, 255));
		HPsprite[i].SetScale({ 10, 10 });

		float offset = (HPsprite[i].GetScale().x * HPsprite[i].GetScale().y + 50) * i;
		HPsprite[i].SetPosition({ 100 + offset, 100 });
	}
	// ショット撃ってから0.25秒で攻撃中止
	shotAnimEndTimer.SetMaxTime(60 * 0.25f);
}

void Player::Initialize()
{
	SetAngle(START_ANGLE);

	sphereDatas["main"].resize(1);
	sphereDatas["main"][0].SetPosition(GetPosition());
	sphereDatas["main"][0].SetRadius(GetScale().x / 2);

	MelLib::Value2<MelLib::Vector3>segmentPos;
	float offset = 0.01f;

#pragma region 床判定

	segment3DDatas["ground"].resize(2);
	// 右側
	segmentPos.v1 = GetPosition() + MelLib::Vector3(-0.5f, 9, 0);
	segmentPos.v2 = GetPosition() + MelLib::Vector3(-0.5f, 0, 0);
	segment3DDatas["ground"][0].SetPosition(segmentPos);
	// 左側
	segmentPos.v1 = GetPosition() + MelLib::Vector3(0.5f, 9, 0);
	segmentPos.v2 = GetPosition() + MelLib::Vector3(0.5f, 0, 0);
	segment3DDatas["ground"][1].SetPosition(segmentPos);
#pragma endregion

#pragma region 

	segment3DDatas["wall"].resize(3);
	// 上側
	segmentPos.v1 = GetPosition() + MelLib::Vector3(sphereDatas["main"][0].GetRadius(), 9, 0);
	segmentPos.v2 = GetPosition() + MelLib::Vector3(-sphereDatas["main"][0].GetRadius(), 9, 0);
	segment3DDatas["wall"][0].SetPosition(segmentPos);
	// 下側
	segmentPos.v1 = GetPosition() + MelLib::Vector3(sphereDatas["main"][0].GetRadius(), 0, 0);
	segmentPos.v2 = GetPosition() + MelLib::Vector3(-sphereDatas["main"][0].GetRadius(), 0, 0);
	segment3DDatas["wall"][1].SetPosition(segmentPos);

	// 中心
	segmentPos.v1 = GetPosition() + MelLib::Vector3(sphereDatas["main"][0].GetRadius(), 4.5, 0);
	segmentPos.v2 = GetPosition() + MelLib::Vector3(-sphereDatas["main"][0].GetRadius(), 4.5, 0);
	segment3DDatas["wall"][2].SetPosition(segmentPos);
#pragma endregion

	tags.push_back("Player");
	skipCollisionCheckTags.push_back("Bullet");

	modelObjects["main"].SetAnimationPlayFlag(true);

	SetPosition(MelLib::Vector3(690, 3.5f, 0));
}

void Player::Update()
{
	// 一番上に書く

	if (thisState == ThisState::CLEAR)
	{
		// 浮いたままゴールしないようにするために呼び出す
		FallStart(0.0f);
		CalcMovePhysics();

		modelObjects["main"].Update();

		// ゴール処理
		if (hitGround) Clear();

		return;
	}

	if (thisState == ThisState::DEAD
		|| thisState == ThisState::FALL_DEAD)
	{
		modelObjects["main"].Update();
		CalcMovePhysics();
		return;
	}

	GameObject::SetGravutationalAcceleration(gravity.GetValue());

	// 絶対上に書く
	thisState = ThisState::STOP;

	Jump();
	Move();
	Shot();

	// アニメーション処理
	Animation();

	// 落下死確認
	CheckFallDead();

	// 絶対最後に書く
	hitGround = false;

}

void Player::Draw()
{
	AllDraw();

	for (int i = 0; i < HP; i++)
	{
		HPsprite[i].Draw();
	}
}

std::shared_ptr<GameObject> Player::GetNewPtr()
{
	return std::make_shared<Player>();
}

void Player::Hit(const GameObject& object, const ShapeType3D shapeType, const std::string& shapeName, const ShapeType3D hitObjShapeType, const std::string& hitShapeName)
{
	if (typeid(object) == typeid(BaseEnemy) || typeid(object) == typeid(Dorakiti))
	{
		HP--;
	}

	Vector3 position = GetPosition();
	if (typeid(object) == typeid(Stage)
		&& shapeType == ShapeType3D::SEGMENT)
	{
		// 床判定
		if (GetHitTriangleData().GetNormal().y >= 0.5f)
		{
			FallEnd();

			Segment3DCalcResult result = GetSegmentCalcResult();

			const float ADD_Y = result.triangleHitPos.y - GetPosition().y;
			AddPosition(Vector3(0, ADD_Y, 0));

			//jumping = false;
			hitGround = true;
		}
		else // 壁判定 
		{
			Segment3DCalcResult result = GetSegmentCalcResult();

			if (GetHitTriangleData().GetNormal().x == 1.0f)
			{
				const float ADD_X = result.triangleHitPos.x - GetPosition().x + sphereDatas["main"][0].GetRadius();
				AddPosition(Vector3(ADD_X, 0, 0));
			}
			else if (GetHitTriangleData().GetNormal().x == -1.0f)
			{
				const float ADD_X = result.triangleHitPos.x - GetPosition().x - sphereDatas["main"][0].GetRadius();
				AddPosition(Vector3(ADD_X, 0, 0));
			}
		}
	}

	if (typeid(object) == typeid(Goal))
	{
		thisState = ThisState::CLEAR;
	}
}

bool Player::GetClear() const
{
	return modelObjects.at("main").GetCurrentAnimationName() == "Goal"
		&& modelObjects.at("main").GetAnimationEndFlag();
}

bool Player::GetDead() const
{
	return modelObjects.at("main").GetCurrentAnimationName() == "Dead"
		&& modelObjects.at("main").GetAnimationEndFlag()
		|| thisState == ThisState::FALL_DEAD;
}

void Player::Move()
{
	Vector3 position = GetPosition();
	Vector3 cpos = Camera::Get()->GetCameraPosition();

	if (Input::KeyState(DIK_A) || Input::KeyState(DIK_D))
	{
		if (Input::KeyState(DIK_A))
		{
			position.x -= speed.GetValue();
			playerDirLeft = true;
		}
		else if (Input::KeyState(DIK_D))
		{
			position.x += speed.GetValue();
			playerDirLeft = false;
		}

		// 移動で少し浮くからhitGroundじゃダメ
		// 一旦浮かなくした
		if (hitGround) thisState = ThisState::DASH;
	}

	MoveRot();

	cpos = Vector3(position.x, position.y + 10, 0);
	Camera::Get()->SetRotateCriteriaPosition(cpos);

	SetPosition(position);
}

void Player::Jump()
{
	Vector3 position = GetPosition();

	if (Input::KeyTrigger(DIK_SPACE)/* && jump == ON_GROUND*/)
	{
		power.SetValue(0.5f);
		FallStart(power.GetValue());
		//jumping = true;

	}
	else
		if (hitGround)FallStart(0);


	////if (/*jump == STAY_IN_AIR*/)
	//{
	//	power.SetValue(0.0f);
	//	FallStart(power.GetValue());
	//	//jump = FALLING;
	//}

	if (!hitGround)thisState = ThisState::JUMP;

	CalcMovePhysics();
}

void Player::Shot()
{

	Vector3 position = GetPosition();
	Vector2 mousevec = Input::GetMouseVector(mousecenter);
	float angle = -atan2f(mousevec.y, mousevec.x) * 180 / PI;

	if (Input::MouseButtonTrigger(MouseButton::LEFT))
	{
		std::shared_ptr<Bullet>b = std::make_shared<Bullet>();
		MelLib::GameObjectManager::GetInstance()->AddObject(b);
		b->SetParameter(position, angle);

		if (!isShotAnimation)
		{
			// 腕のアニメーションデータをリセット
			ResetArmAnimationData();
		}

		isShotAnimation = true;
		// ショット撃ったらリセットして再生
		shotAnimEndTimer.ResetTimeZero();
		shotAnimEndTimer.SetStartFlag(true);
	}
}

void Player::CheckFallDead()
{
	if (GetPosition().y <= Stage::GetDeadPositionY())
	{
		// 死亡処理
		thisState = ThisState::FALL_DEAD;

		// ここに体力をゼロにする処理

	}
}

void Player::MoveRot()
{

	// 回転範囲を正の数じゃなくて負の数の方が振り返りでプレイヤーの顔見れていいかも

	// 最大回転量
	const float ANGLE_MAX = 90.0f;
	// 1フレームの回転量
	const float FRAME_ANGLE = 15.0f;

	// 回転量
	float rotAngle = FRAME_ANGLE;
	if (playerDirLeft) rotAngle *= -1;

	MelLib::Vector3 angle = GetAngle();
	angle.y += rotAngle;
	if (angle.y >= ANGLE_MAX + DEFORT_ANGLE.y)
	{
		angle.y = ANGLE_MAX + DEFORT_ANGLE.y;
	}
	else if (angle.y <= -ANGLE_MAX + DEFORT_ANGLE.y)
	{
		angle.y = -ANGLE_MAX + DEFORT_ANGLE.y;
	}

	SetAngle(angle);
}

void Player::Animation()
{
	std::string animName;
	switch (thisState)
	{
	case Player::ThisState::STOP:
		animName = "Stop";
		break;
	case Player::ThisState::DASH:
		animName = "Dash";
		break;
	case Player::ThisState::JUMP:
		animName = "Jump";
		break;
	case Player::ThisState::DEAD:
		animName = "Dead";
		break;
	default:
		break;
	}

	modelObjects["main"].SetAnimation(animName);
	SetArmAnimation(animName);
	SetAnimationData();

	modelObjects["main"].Update();
	//if (animName == "Dash")DashAnimationAddPosition();
}

void Player::SetArmAnimation(const std::string& animName)
{
	// ショットアニメーションはループしないようにする
	// ダッシュとか停止でショットアニメーション分けないと首伸びてキモイ

	// 時間でショットアニメーション終了
	if (shotAnimEndTimer.GetMaxOverFlag())
	{
		isShotAnimation = false;

		// タイマー終了
		shotAnimEndTimer.ResetTimeZero();
		shotAnimEndTimer.SetStartFlag(false);
	}

	if (isShotAnimation)
	{
		// ショットアニメーションセット
		for (const auto& bone : SET_SHOT_ANIM_BONE)
		{
			modelObjects["main"].SetAnimation("Shot", bone);
		}
	}
	else
	{
		// 通常セット
		for (const auto& bone : SET_SHOT_ANIM_BONE)
		{
			modelObjects["main"].SetAnimation(animName, bone);
		}
	}
}

void Player::DashAnimationAddPosition()
{
	const int ANIM_FRAME = modelObjects["main"].GetAnimationFrame();
	bool up = ANIM_FRAME >= 0 && ANIM_FRAME < 30;
	up = up || ANIM_FRAME <= 60 && ANIM_FRAME < 90;

	bool down = ANIM_FRAME >= 30 && ANIM_FRAME < 60;
	down = down || ANIM_FRAME >= 90 && ANIM_FRAME < 120;

	const float FRAME_ADD = 0.05f;
	if (up)
	{
		//AddPosition(MelLib::Vector3(0, FRAME_ADD, 0));
		modelObjects["main"].SetPosition(modelObjects["main"].GetPosition() + MelLib::Vector3(0, FRAME_ADD, 0));
	}
	else
	{
		//AddPosition(MelLib::Vector3(0, -FRAME_ADD, 0));
		modelObjects["main"].SetPosition(modelObjects["main"].GetPosition() + MelLib::Vector3(0, -FRAME_ADD, 0));
	}
}

void Player::SetAnimationData()
{
	const std::string CURRENT_ANIMATION_OTHER = modelObjects["main"].GetCurrentAnimationName("UpBody");
	if (CURRENT_ANIMATION_OTHER == "Dash")
	{
		modelObjects["main"].SetAnimationEndStopFlag(false);
	}
	else
	{
		modelObjects["main"].SetAnimationEndStopFlag(true);
	}

	SetArmAnimationData();
}

void Player::SetArmAnimationData()
{
	bool endStop = true;

	// ダッシュ中かつショットしてなかったらだったらアニメーションストップしない
	if (thisState == ThisState::DASH && !isShotAnimation)
	{
		endStop = false;
	}

	for (const auto& name : SET_SHOT_ANIM_BONE)
	{
		modelObjects["main"].SetAnimationEndStopFlag(endStop, name);
	}
}

void Player::ResetArmAnimationData()
{
	for (const auto& name : SET_SHOT_ANIM_BONE)
	{
		modelObjects["main"].SetAnimationFrame(0);
	}
}

void Player::Clear()
{
	float cameraDis = MelLib::Camera::Get()->GetCameraToTargetDistance();
	if (cameraDis > 20.0f)
	{
		modelObjects["main"].SetAnimation("Stop");
		modelObjects["main"].SetAnimationFrame(0);
		MelLib::Camera::Get()->SetCameraToTargetDistance(cameraDis - 2.0f);

		MelLib::Vector3 position = GetPosition();
		MelLib::Vector3 cPos = Vector3(position.x, position.y + 10, 0);
		Camera::Get()->SetRotateCriteriaPosition(cPos);

		return;
	}

	if (setGoalAnimData) return;

	// ゴールアニメーション
	modelObjects["main"].SetAnimation("Goal");
	modelObjects["main"].SetAnimationFrame(0);
	modelObjects["main"].SetAnimationEndStopFlag(true);

	setGoalAnimData = true;

	SetAngle({ 0,90,0 });
}
