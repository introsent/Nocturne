#pragma once
#include <vector>
#include <memory>
#include <vec2.hpp>
#include "Event.h"
#include "ColorRule.h" 

class Tile;
class Level
{
public:
    explicit Level(int levelNumber, int stageNumber, int numRows = 7);
    ~Level();

    // New method to get level number
    int GetLevelNumber() const { return m_levelNumber; }
    int GetStageNumber() const { return m_stageNumber; }

    void HandleJump(const glm::ivec2& gridPos);
    void CheckForComplition();
    bool IsCompleted() const;
    Tile* GetTileAt(const glm::ivec2& gridPos) const;
    const std::vector<std::unique_ptr<Tile>>& GetTiles() const;

    bool IsOffGrid(const glm::ivec2& gridPos) const;

	int GetRows() const { return m_rows; }

    // Events
    Event<const Tile&> OnTileColored;
    Event<> OnLevelCompleted;

private:
    void CreateTiles();
    void ConfigureTiles() const;
    void InitializeTileListeners();

    void CreateDiscTiles();
    void CreateDeathBorder();

    int m_levelNumber; 
    int m_stageNumber;
    int m_rows;
    std::vector<std::unique_ptr<Tile>> m_tiles;
    std::unique_ptr<ColorRule> m_colorRule;
    bool m_hasCompleted{ false };
};