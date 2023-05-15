#pragma once
#include <Scene.h>
class Play :
    public MelLib::Scene
{
private:


public:
    void Initialize()override;//初期化
    void Update()override;
    void Draw()override;
    void Finalize()override;//終了処理
    Scene* GetNextScene()override;//次のシーンの指定
};

