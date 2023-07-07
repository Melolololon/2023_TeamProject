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
    // �Ə�
    std::unique_ptr<CursorTexture> cursorTexture;
    MelLib::Sprite2D operationSprite;

    Player* player = nullptr;

    ClearStaging clearStaging; 
    GameOverStaging gameOverStaging;
    // �e��Ԃ��Ƃ̍X�V����
    

private:

    // �N���A
    void ClearUpdate();
    void ClearDraw();

    void GameOverUpdate();
    void GameOverDraw();
public:
    void Initialize()override;//������
    void Update()override;
    void Draw()override;
    void Finalize()override;//�I������
    Scene* GetNextScene()override;//���̃V�[���̎w��
};

