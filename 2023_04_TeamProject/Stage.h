#pragma once
#include <GameObject.h>
class Stage :
    public MelLib::GameObject
{
private:
	// メッシュから三角形の判定を取得
	void SetMeshTriangle();

public:
	Stage();

	void Initialize();

	//更新
	void Update();
	//描画
	void Draw();

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
		const MelLib::ShapeType3D shapeType,
		const std::string& shapeName,
		const MelLib::ShapeType3D hitObjShapeType,
		const std::string& hitShapeName
	);

	std::shared_ptr<GameObject> GetNewPtr();
};

