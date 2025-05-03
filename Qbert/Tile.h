#pragma once
#include <vec2.hpp>

class Tile {
public:
    explicit Tile(const glm::ivec2& gridPos);

    // Color state management
    void SetStartColor(int color);
    void SetIntermediateColor(int color);
    void SetTargetColor(int color);
    void SetToStart();
    void SetToIntermediate();
    void SetToTarget();

    // State queries
    bool HasReachedTarget() const;
    bool IsInIntermediateState() const;
    int GetColorIndex() const;
    void SetColorIndex(int index);

    // Position
    glm::ivec2 GetGridPosition() const;
    bool IsOccupied() const;
    void SetOccupied(bool occupied);

private:
    glm::ivec2 m_gridPos;
    int m_colorIndex;
    int m_startColor{ 0 };
    int m_intermediateColor{ -1 };
    int m_targetColor{ 1 };
    bool m_isOccupied{ false };
};