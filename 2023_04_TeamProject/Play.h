#pragma once
#include <Scene.h>

#include"Player.h"
#include"BackGround.h"


#include"ClearStaging.h"

class Play :
    public MelLib::Scene
{
private:
    enum class GameState 
    {
        PLAY,
        CLEAR,
        GAMEOVER,
    };

    GameState gameState = GameState::PLAY;

    BackGround backGround;
    MelLib::Sprite2D operationSprite;

    std::shared_ptr<Player> player;

    ClearStaging clearStaging;

    // 各状態ごとの更新処理
    
    // クリア
    void ClearUpdate();
    void ClearDraw();

public:
    void Initialize()override;//初期化
    void Update()override;
    void Draw()override;
    void Finalize()override;//終了処理
    Scene* GetNextScene()override;//次のシーンの指定
};

