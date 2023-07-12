#pragma once
#include <GameObject.h>
#include<Easing.h>


// 動く床 ドラキチと同じ
class MoveFloor :
    public MelLib::GameObject
{
private:
    MelLib::Easing<float> easing;

    // 動く床の範囲
    // 場面によって移動量が変わるため、GUIでいじれるようにする
    MelLib::GuiFloat moveUp;
public:
    MoveFloor();
    void Initialize();
    void Update()override;

    std::shared_ptr<GameObject> GetNewPtr() override;
};

