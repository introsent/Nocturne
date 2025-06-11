#include "EnemyPrefabs.h"
#include "utils.h"
#include <TranslationComponent.h>
#include <TextureComponent.h>
#include "AnimationComponent.h"
#include "Coily.h"
#include "GameObjectBuilder.h"

EnemyPrefabs::EnemyPrefabs()
{
    m_Prefabs["Coily"] = &CreateCoily;
    //m_Prefabs["Ugg"] = &CreateUgg;
    //m_Prefabs["Wrongway"] = &CreateWrongway;
    //m_Prefabs["Slick"] = &CreateSlick;
    //m_Prefabs["Sam"] = &CreateSam;
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