#pragma once
#include "Component.h"
#include "Level.h"
#include <vector>
#include <memory>
#include "utils.h"
#include <unordered_map>
#include <string>
#include "EnemyPrefabs.h"
#include "LevelData.h"
#include "QbertPositionProxy.h"
#include "PlayerDataComponent.h"

class LevelComponent final : public dae::Component {
public:
    explicit LevelComponent(dae::GameObject* pOwner, int levelIndex, int stageIndex, PlayerDataComponent* playerData);
    ~LevelComponent() override = default;

    void Update(float deltaTime) override;
    void Render() const override {}

    void SetPlayerData(PlayerDataComponent* playerData);

    Event<> OnLevelCompletedEvent;
private:
    PlayerDataComponent* m_pPlayerData;

    std::vector<EnemySpawnData> m_StageEnemies;
    float m_AccumulatedTime = 0.f;
    bool m_LevelCompleted = false;

    std::unique_ptr<Level> m_pLevel;
    std::vector<dae::GameObject*> m_TileGOs;

    dae::GameObject* m_pQBertGO;
    std::unique_ptr<QbertPositionProxy> m_pQbertPositionProxy;

    std::vector<dae::GameObject*> m_DiscGOs;

    int m_LevelIndex{ 0 };
    int m_StageIndex{ 0 };

    std::vector<std::pair<glm::ivec2, dae::GameObject*>> m_DiscList;

    std::vector<std::pair<std::string, glm::ivec2>> m_EnemySpawns;
	std::unique_ptr<EnemyPrefabs> m_enemyPrefabs = std::make_unique<EnemyPrefabs>();


    //Atlas functions
    void SpawnTiles();
    void OnTileColored(const Tile& tile) const;
    int CalculateTileFrame(const Tile& tile) const;

    void OnLevelCompleted();

	//Qbert functions
    void SpawnQBert();
    void BindCommands() const;

    void SpawnDiscs();

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

    static constexpr const char* levelDataPath = "../Data/Level/levels.json";


    bool m_IsEndingAnimationPlaying = false;
    float m_AnimationTimer = 0.0f;
    int m_CurrentAnimationState = 0;
    static constexpr int MAX_ANIMATION_STATES = 3;

    float m_AnimationTotalTime{};
    float m_AnimationStateTime{};

    void PlayEndingAnimation(float deltaTime);
    void UpdateAllTilesToAnimationState();
};