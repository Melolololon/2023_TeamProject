#pragma once
#include <Scene.h>

#include"BackGround.h"

class Play :
    public MelLib::Scene
{
private:
    BackGround backGround;

public:
    void Initialize()override;//������
    void Update()override;
    void Draw()override;
    void Finalize()override;//�I������
    Scene* GetNextScene()override;//���̃V�[���̎w��
};

