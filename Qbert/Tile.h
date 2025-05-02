#pragma once
#include <vec2.hpp>

class Tile
{
public:
    Tile(const glm::ivec2& gridPos);

    // Position accessors
    [[nodiscard]] glm::vec2 GetWorldPosition() const;
    [[nodiscard]] glm::ivec2 GetGridPosition() const;

    // Color state
    [[nodiscard]] int GetColorIndex() const;
    void SetColorIndex(int index);

    // Occupancy
    void SetOccupied(bool occupied);
    [[nodiscard]] bool IsOccupied() const;

    // Color rule helpers
    void SetToStart();
    void SetToIntermediate();
    void SetToTarget();

    bool HasReachedTarget() const;
    bool IsInIntermediateState() const;

private:
    int m_startColor = 0;
    int m_intermediateColor = -1; // -1 means not used
    int m_targetColor = 1;

    int         m_colorIndex = 0;
    bool        m_isOccupied = false;
    glm::ivec2  m_gridPos{};
};
