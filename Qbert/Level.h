#pragma once
#include <vector>
#include <memory>
#include <vec2.hpp>
#include "Event.h"
#include "ColorRule.h"  // Include ColorRule header

class Tile;
class Level
{
public:
    explicit Level(int levelNumber, int numRows = 7);
    ~Level();

    // New method to get level number
    int GetLevelNumber() const { return m_levelNumber; }

    void HandleJump(const glm::ivec2& gridPos);
    bool IsCompleted() const;
    Tile* GetTileAt(const glm::ivec2& gridPos) const;
    const std::vector<std::unique_ptr<Tile>>& GetTiles() const;

    // Events
    Event<const Tile&> OnTileColored;
    Event<> OnLevelCompleted;

private:
    void CreateTiles();
    void ConfigureTiles();

    void CreateDeathBorder();

    int m_levelNumber; 
    int m_rows;
    std::vector<std::unique_ptr<Tile>> m_tiles;
    std::unique_ptr<ColorRule> m_colorRule;
    bool m_hasCompleted{ false };
};