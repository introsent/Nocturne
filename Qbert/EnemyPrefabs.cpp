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

std::shared_ptr<dae::GameObject> EnemyPrefabs::CreateCoily(Level* level, const glm::ivec2& gridPos, QBertPlayer* qbertPlayer) {
    glm::vec2 worldPos = GridToWorldCoily(gridPos);

    auto coily = GameObjectBuilder()
        .WithTranslation()
        .WithTexture("Coily Spritesheet.png", 0.f, 2.f)
        .WithAnimation(glm::vec2(16.f, 32.f), 10, 0.2f, 1, 10)
        .WithComponent<Coily>(gridPos, level, qbertPlayer)
        .SetPosition(glm::vec3(worldPos.x, worldPos.y, 0.f))
        .Build();

    if (auto animationComp = coily->GetComponent<AnimationComponent>()) {
        animationComp->SetFrame(0);
    }

    return coily;
}

std::shared_ptr<dae::GameObject> EnemyPrefabs::CreateEnemy(
    const std::string& type,
    Level* level,
    const glm::ivec2& gridPos, QBertPlayer* qbertPlayer)
{
    if (auto it = m_Prefabs.find(type); it != m_Prefabs.end()) {
        return it->second(level, gridPos, qbertPlayer);
    }
    return nullptr;
}