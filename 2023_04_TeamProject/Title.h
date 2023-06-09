#pragma once
#include <Scene.h>

#include"Sprite2D.h"

class Title :
    public MelLib::Scene
{
private:
    MelLib::Sprite2D titleSprite;

public:
    void Initialize()override;//初期化
    void Update()override;
    void Draw()override;
    void Finalize()override;//終了処理
    Scene* GetNextScene()override;//次のシーンの指定

};

