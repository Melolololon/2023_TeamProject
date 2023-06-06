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

    // �e��Ԃ��Ƃ̍X�V����
    
    // �N���A
    void ClearUpdate();
    void ClearDraw();

public:
    void Initialize()override;//������
    void Update()override;
    void Draw()override;
    void Finalize()override;//�I������
    Scene* GetNextScene()override;//���̃V�[���̎w��
};

