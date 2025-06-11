#include "EnemyPrefabs.h"
#include "utils.h"
#include <TranslationComponent.h>
#include <TextureComponent.h>
#include "AnimationComponent.h"
#include "Coily.h"
#include "GameObjectBuilder.h"
#include "UggWrongway.h"
#include "SlickSam.h"

EnemyPrefabs::EnemyPrefabs()
{
    m_Prefabs["Coily"] = &CreateCoily;
    m_Prefabs["Ugg"] = &CreateUgg;
    m_Prefabs["Wrongway"] = &CreateWrongway;
    m_Prefabs["Slick"] = &CreateSlick;
    m_Prefabs["Sam"] = &CreateSam;
}

std::unique_ptr<dae::GameObject> EnemyPrefabs::CreateEnemy(
    const std::string& type,
    Level* level,
    const glm::ivec2& gridPos, const IPositionProxy& qbertPositionProxy)
{
    if (auto it = m_Prefabs.find(type); it != m_Prefabs.end()) {
        return it->second(level, gridPos, qbertPositionProxy);
    }
    return nullptr;
}

std::unique_ptr<dae::GameObject> EnemyPrefabs::CreateCoily(Level* level, const glm::ivec2& gridPos, const IPositionProxy& qbertPositionProxy) {
    glm::vec2 worldPos = GridToWorldCoily(gridPos);

    auto coily = GameObjectBuilder()
        .WithTranslation()
        .WithTexture("Coily Spritesheet.png", 0.f, 2.f)
        .WithAnimation(glm::vec2(16.f, 32.f), 10, 0.2f, 1, 10)
        .WithComponent<Coily>(gridPos, level, qbertPositionProxy)
        .SetPosition(glm::vec3(worldPos.x, worldPos.y, 0.f))
        .Build();

    if (auto animationComp = coily->GetComponent<AnimationComponent>()) {
        animationComp->SetFrame(0);
    }

    return coily;
}

// Slick/Sam helper
std::unique_ptr<dae::GameObject> EnemyPrefabs::CreateSlickSam(
    Level* level,
    const glm::ivec2& gridPos,
    const IPositionProxy& qbertPositionProxy,
    bool isSlick)
{
    glm::vec2 worldPos = GridToWorld(gridPos);

    auto enemy = GameObjectBuilder()
        .WithTranslation()
        .WithTexture("Slick Sam Spritesheet.png", 0, 2.f)
        .WithAnimation(glm::vec2(12, 16),  // Frame size: 12x16
            4,                  // Total frames: 4
            0.0f,               // FPS (0 = manual control)
            isSlick ? 0 : 2,     // Start frame (Slick: top row, Sam: bottom row)
            2)                   // Frames per row (24px width / 12px = 2)
        .WithComponent<SlickSam>(level, qbertPositionProxy, isSlick)
        .SetPosition(glm::vec3(worldPos.x, worldPos.y, 0.f))
        .Build();

    // Set initial frame based on direction
    if (auto animationComp = enemy->GetComponent<AnimationComponent>()) {
        animationComp->SetFrame(isSlick ? 0 : 2); // Slick left, Sam left
    }

    return enemy;
}

std::unique_ptr<dae::GameObject> EnemyPrefabs::CreateSlick(
    Level* level,
    const glm::ivec2& gridPos,
    const IPositionProxy& qbertPositionProxy)
{
    return CreateSlickSam(level, gridPos, qbertPositionProxy, true);
}

std::unique_ptr<dae::GameObject> EnemyPrefabs::CreateSam(
    Level* level,
    const glm::ivec2& gridPos,
    const IPositionProxy& qbertPositionProxy)
{
    return CreateSlickSam(level, gridPos, qbertPositionProxy, false);
}

// Ugg/Wrongway helper
std::unique_ptr<dae::GameObject> EnemyPrefabs::CreateUggWrongway(
    Level* level,
    const glm::ivec2& gridPos,
    const IPositionProxy& qbertPositionProxy,
    bool isUgg)
{
    glm::vec2 worldPos = GridToWorld(gridPos);

    auto enemy = GameObjectBuilder()
        .WithTranslation()
        .WithTexture("Ugg Wrongway Spritesheet.png", 0.f, 2.f)
        .WithAnimation(glm::vec2(16, 16),  // Frame size: 16x16
            8,                  // Total frames: 8
            0.0f,               // FPS (0 = manual control)
            isUgg ? 0 : 4,      // Start frame (Ugg: top row, Wrongway: bottom row)
            4)                  // Frames per row (64px width / 16px = 4)
        .WithComponent<UggWrongway>(level, qbertPositionProxy, isUgg)
        .SetPosition(glm::vec3(worldPos.x, worldPos.y, 0.f))
        .Build();

    // Set initial frame based on direction
    if (auto animationComp = enemy->GetComponent<AnimationComponent>()) {
        animationComp->SetFrame(isUgg ? 0 : 4); // Ugg frame 0, Wrongway frame 4
    }

    return enemy;
}

std::unique_ptr<dae::GameObject> EnemyPrefabs::CreateUgg(
    Level* level,
    const glm::ivec2& gridPos,
    const IPositionProxy& qbertPositionProxy)
{
    return CreateUggWrongway(level, gridPos, qbertPositionProxy, true);
}

std::unique_ptr<dae::GameObject> EnemyPrefabs::CreateWrongway(
    Level* level,
    const glm::ivec2& gridPos,
    const IPositionProxy& qbertPositionProxy)
{
    return CreateUggWrongway(level, gridPos, qbertPositionProxy, false);
}