#pragma once
#include <Scene.h>

#include"Sprite2D.h"

class Title :
    public MelLib::Scene
{
private:
    MelLib::Sprite2D titleSprite;

public:
    void Initialize()override;//������
    void Update()override;
    void Draw()override;
    void Finalize()override;//�I������
    Scene* GetNextScene()override;//���̃V�[���̎w��

};

