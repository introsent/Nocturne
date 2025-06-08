#pragma once
#include "Component.h"
#include "Level.h"
#include <vector>
#include <memory>
#include "utils.h"
#include <unordered_map>
#include <string>
#include "EnemyPrefabs.h"

class LevelComponent final : public dae::Component {
public:
    explicit LevelComponent(dae::GameObject* pOwner, int levelIndex);
    ~LevelComponent() override = default;

    void Update(float deltaTime) override;
    void Render() const override {}

private:
    std::unique_ptr<Level> m_pLevel;
    std::vector<std::shared_ptr<dae::GameObject>> m_TileGOs;
    std::shared_ptr<dae::GameObject> m_pQBertGO;
    std::vector<std::shared_ptr<dae::GameObject>> m_DiscGOs;

    std::vector<std::pair<glm::ivec2, std::shared_ptr<dae::GameObject>>> m_DiscList;

    std::vector<std::pair<std::string, glm::ivec2>> m_EnemySpawns;
	std::unique_ptr<EnemyPrefabs> m_enemyPrefabs = std::make_unique<EnemyPrefabs>();

    //Atlas functions
    void SpawnTiles();
    void OnTileColored(const Tile& tile) const;

	//Qbert functions
    void SpawnQBert();
    void BindCommands() const;

    void SpawnDiscs();

    void SpawnEnemies();

    struct TextureConfig {
        char const* file;
        glm::vec2  frameSize;
    };

    struct AtlasConfig {
        TextureConfig tex;
        int           columns;
        int           rows;
    };

    // Map atlas:
    static constexpr AtlasConfig m_map{
        { "Qbert Cubes.png", { 32.f, 32.f } },
        /*columns=*/ 6,
        /*rows=*/    3
    };

    // Qbert:
    static constexpr AtlasConfig m_qbert{
        {"Qbert P1 Spritesheet.png",
        { 17.f, 16.f }},
		/*columns=*/ 4,
		/*rows=*/    1
    };

    // Disc:
    static constexpr AtlasConfig m_disc{
        {"Disk Spritesheet.png",
        { 16.f, 10.f }},
		/*columns=*/ 30,
		/*rows=*/    1
    };

    // Coily:
    static constexpr AtlasConfig m_coily{
        { "Coily Spritesheet.png", { 16.f, 32.f}},
        /*columns=*/ 10,
        /*rows=*/    1
    };
};