#pragma once
#include <Scene.h>

#include"Player.h"
#include"BackGround.h"
#include"CursorTexture.h"

#include"ClearStaging.h"
#include"GameOverStaging.h"

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

    std::unique_ptr<BackGround> backGround;
    // 照準
    std::unique_ptr<CursorTexture> cursorTexture;
    MelLib::Sprite2D operationSprite;

    Player* player = nullptr;

    ClearStaging clearStaging; 
    GameOverStaging gameOverStaging;
    // 各状態ごとの更新処理
    

private:

    // クリア
    void ClearUpdate();
    void ClearDraw();

    void GameOverUpdate();
    void GameOverDraw();
public:
    void Initialize()override;//初期化
    void Update()override;
    void Draw()override;
    void Finalize()override;//終了処理
    Scene* GetNextScene()override;//次のシーンの指定
};

