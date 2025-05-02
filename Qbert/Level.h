#pragma once
#include <vector>
#include <memory>
#include <vec2.hpp>
#include "Event.h"

class Tile;
class ColorRule;

class Level
{
public:
    explicit Level(int levelNumber, int numRows = 7);
    ~Level();

    // Called when Q*bert lands on a tile at gridPos
    void HandleJump(const glm::ivec2& gridPos);

    // Query for full completion
    bool IsCompleted() const;

    // Access a specific tile
    Tile* GetTileAt(const glm::ivec2& gridPos) const;
    const std::vector<std::unique_ptr<Tile>>& GetTiles() const;

    // Events
    Event<const Tile&> OnTileColored;    // fires when a tile first hits target color
    Event<>            OnLevelCompleted; // fires once when level is done

private:
    void CreateTiles();
    void ApplyInitialRule();

    int                                   m_rows;
    std::vector<std::unique_ptr<Tile>>    m_tiles;
    std::unique_ptr<ColorRule>            m_colorRule;
    bool                                  m_hasCompleted{ false };
};
