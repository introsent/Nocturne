#pragma once
#include "SimpleEnemy.h"

class SlickSam : public SimpleEnemy {
public:
    SlickSam(dae::GameObject* owner, Level* level,
        const IPositionProxy& qbertPositionProxy, bool isSlick);

    bool ShouldDamageQBert() const override { return false; }

private:
    void GenerateNextMove() override;
    void OnLand() override;

    bool m_isSlick; 
};