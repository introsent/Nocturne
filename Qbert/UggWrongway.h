#pragma once
#include "SimpleEnemy.h"
#include <vector>

class UggWrongway : public SimpleEnemy {
public:
    UggWrongway(dae::GameObject* owner, Level* level,
        const IPositionProxy& qbertPositionProxy, bool isUgg);

private:
    void GenerateNextMove() override;
    void OnLand() override;

    bool m_isUgg;
    std::vector<glm::ivec2> m_directionSequence;
    int m_currentDirectionIndex = 0;
};