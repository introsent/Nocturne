#pragma once
#include <vec2.hpp>
#include "Event.h"

enum class TileType { NORMAL, DEATH, DISC };

class Tile {
public:
    explicit Tile(const glm::ivec2& gridPos, TileType type = TileType::NORMAL);

    // Color state management
    void SetStartColor(int color);
    void SetIntermediateColor(int color);
    void SetTargetColor(int color);
    void SetToStart();
    void SetToIntermediate();
    void SetToTarget();

    // New methods
    void ChangeColor(int change);
    void RevertColor();

    // Event for color changes
    Event<Tile&> OnColorChanged;

    // State queries
    bool HasReachedTarget() const;
    bool IsInIntermediateState() const;
    int GetColorIndex() const;
    void SetColorIndex(int index); 

    TileType GetType() const { return m_type; }
    void SetType(TileType type) { m_type = type; }

    // Position
    glm::ivec2 GetGridPosition() const;
    bool IsOccupied() const;
    void SetOccupied(bool occupied);

private:
    TileType m_type;
    glm::ivec2 m_gridPos;
    int m_colorIndex;
    int m_startColor{ 0 };
    int m_intermediateColor{ -1 };
    int m_targetColor{ 1 };
    bool m_isOccupied{ false };
};