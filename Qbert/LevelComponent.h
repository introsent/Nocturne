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
#include "GameMode.h"

enum class InputDevice { Keyboard, Controller0, Controller1 };

class LevelComponent final : public dae::Component {
public:
    explicit LevelComponent(dae::GameObject* pOwner, int levelIndex, int stageIndex, PlayerDataComponent* playerData, GameMode mode);
    ~LevelComponent() override = default;

    void Update(float deltaTime) override;
    void Render() const override {}

    void SetPlayerData(PlayerDataComponent* playerData);

    Event<> OnLevelCompletedEvent;
private:
    void SpawnTiles();
    void SpawnDiscs();
    void SpawnPlayers();
    dae::GameObject* SpawnQBertAt(const glm::ivec2& gridPos, InputDevice device, bool isSecondPLayer);
    dae::GameObject* SpawnPlayerCoily();
    void BindCommands();
    void BindQBertInputs(dae::GameObject* qbertGO, InputDevice device);
    void BindCoilyInputs(dae::GameObject* coilyGO, InputDevice device);
    void OnTileColored(const Tile& tile) const;
    int CalculateTileFrame(const Tile& tile) const;
    void OnLevelCompleted();
    void PlayEndingAnimation(float deltaTime);
    void UpdateAllTilesToAnimationState();

    std::unique_ptr<Level> m_pLevel{};
    int m_LevelIndex{};
    int m_StageIndex{};
    PlayerDataComponent* m_pPlayerData{};
    std::vector<dae::GameObject*> m_TileGOs{};
    std::vector<dae::GameObject*> m_DiscGOs{};
    std::vector<dae::GameObject*> m_QbertGOs{};
    dae::GameObject* m_CoilyGO{ nullptr };
    std::unique_ptr<QbertPositionProxy> m_pQbertPositionProxy{};
    std::vector<EnemySpawnData> m_StageEnemies{};
    std::unique_ptr<EnemyPrefabs> m_enemyPrefabs{ std::make_unique<EnemyPrefabs>() };

    float m_AccumulatedTime{ 0.f };
    bool m_LevelCompleted{ false };
    bool m_IsEndingAnimationPlaying{ false };
    float m_AnimationTotalTime{};
    float m_AnimationStateTime{};
    int m_CurrentAnimationState{};
    static constexpr int MAX_ANIMATION_STATES{ 3 };

    GameMode m_Mode;

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

    static constexpr AtlasConfig m_qbert2{
       {"Qbert P2 Spritesheet.png",
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
};