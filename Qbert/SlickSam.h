#pragma once
#include "SimpleEnemy.h"

class SlickSam : public SimpleEnemy {
public:
    SlickSam(dae::GameObject* owner, Level* level,
        const IPositionProxy& qbertPositionProxy, bool isSlick);

private:
    void GenerateNextMove() override;
    void OnLand() override;

    bool m_isSlick; 
};