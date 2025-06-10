#include "EnemyPrefabs.h"
#include "utils.h"
#include <TranslationComponent.h>
#include <TextureComponent.h>
#include "AnimationComponent.h"
#include "Coily.h"

EnemyPrefabs::EnemyPrefabs()
{
    m_Prefabs["Coily"] = &CreateCoily;
    //m_Prefabs["Ugg"] = &CreateUgg;
    //m_Prefabs["Wrongway"] = &CreateWrongway;
    //m_Prefabs["Slick"] = &CreateSlick;
    //m_Prefabs["Sam"] = &CreateSam;
}

std::shared_ptr<dae::GameObject> EnemyPrefabs::CreateCoily(Level* level, const glm::ivec2& gridPos, QBertPlayer* qbertPlayer) {
    auto coily = std::make_shared<dae::GameObject>();

    glm::vec2 worldPos = GridToWorldCoily(gridPos);
    coily->AddComponent<dae::TranslationComponent>(coily.get());

    // Configure Coily-specific components
    auto textureComp = coily->AddComponent<dae::TextureComponent>(coily.get(), "Coily Spritesheet.png", 0.f, 2.f);
    auto animationComp = coily->AddComponent<AnimationComponent>(
        coily.get(),
        textureComp,
        glm::vec2(16.f, 32.f), // Frame size
        10,                    // Total frames
        0.2f,                  // Time per frame
        1,                     // Rows
        10                     // Columns
    );
    animationComp->SetFrame(0);

    coily->AddComponent<Coily>(coily.get(), gridPos, level, qbertPlayer);

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