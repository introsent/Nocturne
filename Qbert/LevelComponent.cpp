#include "LevelComponent.h"
#include "GameObject.h"
#include "TranslationComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "ScoreComponent.h"
#include "Tile.h"

#include <array>
#include <iostream>

#include "Scene.h"
#include "SceneManager.h"

static constexpr char const* TileAtlasFile = "../Data/Qbert Cubes.png";
static constexpr glm::vec2 FrameSize = { 32.f, 32.f };

// Helper to convert tile grid coords to world space (assuming isometric projection)
namespace {
    glm::vec2 GridToWorld(const glm::ivec2& gridPos) {
        constexpr glm::vec2 Origin{ 400.f, 100.f };  // Center point
        constexpr float VisualTileW = 64.f;  // Display width (twice frame width)
        constexpr float VisualTileH = 32.f;  // Display height

        int row = gridPos.y;
        int col = gridPos.x;

        // Q*bert's classic isometric projection
        float x = Origin.x + (col - row) * (VisualTileW * 0.5f);
        float y = Origin.y + (col + row) * (VisualTileH * 0.5f);

        return { x, y };
    }
}

LevelComponent::LevelComponent(dae::GameObject* owner, int levelIndex)
    : Component(owner)
    , m_pLevel(std::make_unique<Level>(levelIndex))
{
    SpawnTiles();

    m_pLevel->OnTileColored.Subscribe(
        [this](const Tile& tile) { OnTileColored(tile); }
    );

    //SpawnQBert();
    //SpawnDiscs();
}

void LevelComponent::Update(float)
{
   // m_pLevel->Update(deltaTime);
}

void LevelComponent::SpawnTiles()
{
    auto texture = dae::ResourceManager::GetInstance().LoadTexture(TileAtlasFile);

    for (auto const& tilePtr : m_pLevel->GetTiles())
    {
        const Tile& tile = *tilePtr;

        auto tileGO = std::make_shared<dae::GameObject>();

        glm::vec2 worldPos = GridToWorld(tile.GetGridPosition());
        tileGO->AddComponent<dae::TranslationComponent>(tileGO.get());
        tileGO->GetComponent<dae::TranslationComponent>()->Translate(glm::vec3(worldPos.x, worldPos.y, 0.f));

        auto textureComp = tileGO->AddComponent<dae::TextureComponent>(tileGO.get(), TileAtlasFile);

        auto animationComp = tileGO->AddComponent<AnimationComponent>(
            tileGO.get(),
            textureComp,
            FrameSize,  // 32x32
            6,          // 6 columns in atlas
            0.f         // no auto-advance
        );
        animationComp->SetFrame(tile.GetColorIndex());

        m_TileGOs.push_back(tileGO);
        dae::Scene* activeScene = dae::SceneManager::GetInstance().GetActiveScene();
        if (activeScene) {
            activeScene->Add(tileGO);
        }
        else {
            // Handle the error if the active scene is null
            std::cerr << "Active scene is null!" << std::endl;
        }

    }
}

void LevelComponent::OnTileColored(const Tile& tile)
{
    const glm::vec2 targetWorldPos = tile.GetWorldPosition();

    for (auto& tileGO : m_TileGOs)
    {
        const glm::vec3 currentPos3D = tileGO->GetWorldPosition();
        const glm::vec2 currentPos = { currentPos3D.x, currentPos3D.y };

        const float tolerance = 0.01f;
        if (std::abs(currentPos.x - targetWorldPos.x) < tolerance &&
            std::abs(currentPos.y - targetWorldPos.y) < tolerance)
        {
            if (auto* animComp = tileGO->GetComponent<AnimationComponent>())
            {
                animComp->SetFrame(tile.GetColorIndex());
            }
            break;
        }
    }
}

void LevelComponent::SpawnQBert()
{
    auto qbertGO = std::make_shared<dae::GameObject>();

    auto startTile = m_pLevel->GetTileAt({ 0, 0 });
    glm::vec2 worldPos = GridToWorld(startTile->GetGridPosition());

    qbertGO->AddComponent<dae::TranslationComponent>(qbertGO.get());
    qbertGO->GetComponent<dae::TranslationComponent>()->Translate(glm::vec3(worldPos.x, worldPos.y, 0.f));
    auto textureComp = qbertGO->AddComponent<dae::TextureComponent>(qbertGO.get(), "QBert.png");

    qbertGO->AddComponent<AnimationComponent>(
        qbertGO.get(),
        textureComp,
        glm::vec2{ 64.f, 64.f },
        4,
        0.2f
    );

    //qbertGO->AddComponent<QBertComponent>(qbertGO.get(), m_pLevel.get());

    m_pQBertGO = qbertGO;
    dae::SceneManager::GetInstance().GetActiveScene()->Add(qbertGO);
}

void LevelComponent::SpawnDiscs()
{
    std::array<glm::vec2, 2> discPositions = {
        glm::vec2{200.f, 300.f},
        glm::vec2{600.f, 300.f}
    };

    dae::ResourceManager::GetInstance().LoadTexture("Disc.png");

    for (auto const& pos : discPositions)
    {
        auto discGO = std::make_shared<dae::GameObject>();
        discGO->AddComponent<dae::TranslationComponent>(discGO.get());
        discGO->GetComponent<dae::TranslationComponent>()->Translate(glm::vec3(pos.x, pos.y, 0.f));

        discGO->AddComponent<dae::TextureComponent>(discGO.get(), "Disc.png");

        glm::vec2 targetPos = GridToWorld(m_pLevel->GetTileAt({ 0,0 })->GetGridPosition());
        //discGO->AddComponent<DiscComponent>(discGO.get(), pos, targetPos);

        m_DiscGOs.push_back(discGO);
        dae::SceneManager::GetInstance().GetActiveScene()->Add(discGO);
    }
}
