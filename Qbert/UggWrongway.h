#pragma once
#include <array>
#include "SimpleEnemy.h"

class UggWrongway : public SimpleEnemy {
public:
    UggWrongway(dae::GameObject* owner, Level* level, glm::ivec2 spawnGridPosition,
        const IPositionProxy& qbertPositionProxy, bool isUgg);

private:
    void GenerateNextMove() override;
    void OnLand() override;

    static constexpr glm::ivec2 UP_LEFT{ -1, -1 };
    static constexpr glm::ivec2 UP_RIGHT{ 0, -1 };

    static constexpr glm::ivec2 LEFT{ -1, 0 };
    static constexpr glm::ivec2 RIGHT{ 1, 0 };

    static constexpr std::array<glm::ivec2, 4> SPRITE_DIRECTIONS = { RIGHT, UP_RIGHT, LEFT, UP_LEFT };

    bool m_isUgg;

    glm::ivec2 m_direction{};
    int m_currentDirectionIndex = 0;
};