#pragma once
#include "Component.h"
#include "Level.h"
#include <vector>
#include <memory>

class LevelComponent final : public dae::Component
{
public:
    explicit LevelComponent(dae::GameObject* pOwner, int levelIndex);
    ~LevelComponent() override = default;

    void Update(float deltaTime) override;

    void Render() const override {}

private:
    std::unique_ptr<Level> m_pLevel;

    // keep all tile GOs alive
    std::vector<std::shared_ptr<dae::GameObject>> m_TileGOs;
    std::shared_ptr<dae::GameObject>              m_pQBertGO;
    std::vector<std::shared_ptr<dae::GameObject>> m_DiscGOs;

    // Helpers
    void SpawnTiles();
    void SpawnQBert();
    void SpawnDiscs();

    // Called when a Tile changes color
    void OnTileColored(const Tile& tile);
};
