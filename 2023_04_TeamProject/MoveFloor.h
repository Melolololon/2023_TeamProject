#pragma once
#include <GameObject.h>
#include<Easing.h>


// ������ �h���L�`�Ɠ���
class MoveFloor :
    public MelLib::GameObject
{
private:
    MelLib::Easing<float> easing;

    // �������͈̔�
    // ��ʂɂ���Ĉړ��ʂ��ς�邽�߁AGUI�ł������悤�ɂ���
    MelLib::GuiFloat moveUp;
public:
    MoveFloor();
    void Initialize();
    void Update()override;

    std::shared_ptr<GameObject> GetNewPtr() override;
};

