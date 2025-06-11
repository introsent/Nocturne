#include "LevelComponent.h"
#include "GameObject.h"
#include "TranslationComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "QBertPlayer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Tile.h"
#include "utils.h"
#include "DiscManager.h"
#include "Directions.h"
#include "Coily.h"
#include "EnemyPrefabs.h"
#include "GameObjectBuilder.h"
#include <ranges> 

LevelComponent::LevelComponent(dae::GameObject* owner, int levelIndex, int stageIndex)
    : Component(owner)
    , m_pLevel(std::make_unique<Level>(levelIndex))
    , m_LevelIndex(levelIndex)
    , m_StageIndex(stageIndex)
{

    auto levels = LevelDataLoader::LoadLevels("../Data/Level/levels.json");
    for (const auto& level : levels) {
        if (level.index == levelIndex) {
            for (const auto& stage : level.stages) {
                if (stage.stage == stageIndex) {
                    m_StageEnemies = stage.enemies;
                    break;
                }
            }
            break;
        }
    }

    SpawnTiles();
    SpawnDiscs();
    SpawnQBert();

    m_pLevel->OnTileColored.Subscribe([this](const Tile& tile) { OnTileColored(tile); });
    m_pLevel->OnLevelCompleted.Subscribe([this]() { OnLevelCompleted(); });
}

void LevelComponent::Update(float deltaTime) {
    if (m_LevelCompleted) return;

    m_AccumulatedTime += deltaTime;

    // Spawn enemies based on timing
    for (auto it = m_StageEnemies.begin(); it != m_StageEnemies.end(); ) {
        if (m_AccumulatedTime >= it->spawn_time) {
            auto enemyGO = m_enemyPrefabs->CreateEnemy(
                it->type,
                m_pLevel.get(),
                it->start_position,
                *m_pQbertPositionProxy
            );

            enemyGO->GetComponent<Enemy>()->OnCollisionWithQbert.Subscribe([this](dae::GameObject* enemy) {
                m_pQBertGO->GetComponent<QBertPlayer>()->TakeHit();
                enemy->MarkForDestroy();
            });

            if (enemyGO && dae::SceneManager::GetInstance().GetActiveScene()) {
                dae::SceneManager::GetInstance().GetActiveScene()->Add(std::move(enemyGO));
            }
            it = m_StageEnemies.erase(it);
        }
        else {
            ++it;
        }
    }
}



void LevelComponent::SpawnTiles() {
    for (auto const& tilePtr : m_pLevel->GetTiles()) {
        if (tilePtr->GetType() == TileType::DEATH || tilePtr->GetType() == TileType::DISC) continue;
        const Tile& tile = *tilePtr;

        glm::vec2 worldPos = GridToWorld(tile.GetGridPosition());

        auto tileGO = GameObjectBuilder()
            .WithTranslation()
            .WithTexture(m_map.tex.file, -0.5f, 2.f)
            .WithAnimation(m_map.tex.frameSize, m_map.rows * m_map.columns, 0.f, m_map.rows, m_map.columns)
            .SetPosition(glm::vec3(worldPos.x, worldPos.y, -tile.GetGridPosition().y))
            .Build();

        // Set the frame based on tile state
        if (auto animationComp = tileGO->GetComponent<AnimationComponent>()) {
            const int stateRow = tile.GetColorIndex();
            const int levelColumn = m_pLevel->GetLevelNumber() - 1;
            const int frame = stateRow * 6 + levelColumn;
            animationComp->SetFrame(frame);
        }


        m_TileGOs.emplace_back(tileGO.get());
        if (auto scene = dae::SceneManager::GetInstance().GetActiveScene()) {
            scene->Add(std::move(tileGO));
        }
    }
}

void LevelComponent::OnTileColored(const Tile& tile) const
{
    const int levelNumber = m_pLevel->GetLevelNumber();
    const int levelColumn = levelNumber - 1;
    const int stateRow = tile.GetColorIndex();
    const int frame = stateRow * 6 + levelColumn;

    for (auto& tileGO : m_TileGOs) {
        const glm::vec2 currentPos = {
            tileGO->GetWorldPosition().x,
            tileGO->GetWorldPosition().y
        };

        if (currentPos == GridToWorld(tile.GetGridPosition())) {
            if (auto animComp = tileGO->GetComponent<AnimationComponent>()) {
                animComp->SetFrame(frame);
            }
            break;
        }
    }
}
void LevelComponent::OnLevelCompleted()
{
    m_LevelCompleted = true;
    dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
}

void LevelComponent::SpawnQBert() {
    auto startTile = m_pLevel->GetTileAt({ 0, 0 });
    glm::vec2 worldPos = GridToWorldCharacter(startTile->GetGridPosition());

    auto qbertGO = GameObjectBuilder()
        .WithTranslation()
        .WithTexture(m_qbert.tex.file, 0.f, 2.f)
        .WithAnimation(m_qbert.tex.frameSize, m_qbert.columns * m_qbert.rows, 0.2f, m_qbert.rows, m_qbert.columns)
        .WithComponent<QBertPlayer>(m_pLevel.get())
        .SetPosition(glm::vec3(worldPos.x, worldPos.y, 0.f))
        .Build();

    if (auto animationComp = qbertGO->GetComponent<AnimationComponent>()) {
        animationComp->SetFrame(3);
    }

    m_pQBertGO = qbertGO.get();
    if (auto scene = dae::SceneManager::GetInstance().GetActiveScene()) {
        scene->Add(std::move(qbertGO));
    }

    BindCommands();

    auto qbertPlayer = m_pQBertGO->GetComponent<QBertPlayer>();
    m_pQbertPositionProxy = std::make_unique<QbertPositionProxy>(qbertPlayer);

    qbertPlayer->OnPositionChanged.Subscribe([this](const glm::ivec2& newPos) {
        m_pQbertPositionProxy->UpdatePosition(newPos);
    });
  
}

void LevelComponent::BindCommands() const
{
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, InputState::Up,
		std::make_unique<MoveCommand>(m_pQBertGO, UP_RIGHT));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, InputState::Up,
		std::make_unique<MoveCommand>(m_pQBertGO, DOWN_LEFT));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, InputState::Up,
		std::make_unique<MoveCommand>(m_pQBertGO,UP_LEFT));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, InputState::Up,
		std::make_unique<MoveCommand>(m_pQBertGO,  DOWN_RIGHT));


    dae::InputManager::GetInstance().BindControllerCommand(dae::XInputManager::GetXInputValue(GamepadButton::DpadUp), InputState::Pressed,
                                                           std::make_unique<MoveCommand>(m_pQBertGO, UP_RIGHT));   // Up
    dae::InputManager::GetInstance().BindControllerCommand(dae::XInputManager::GetXInputValue(GamepadButton::DpadDown), InputState::Pressed,
                                                           std::make_unique<MoveCommand>(m_pQBertGO, DOWN_LEFT));    // Down
    dae::InputManager::GetInstance().BindControllerCommand(dae::XInputManager::GetXInputValue(GamepadButton::DpadLeft), InputState::Pressed,
                                                           std::make_unique<MoveCommand>(m_pQBertGO, UP_LEFT));   // Left
    dae::InputManager::GetInstance().BindControllerCommand(dae::XInputManager::GetXInputValue(GamepadButton::DpadRight), InputState::Pressed,
                                                           std::make_unique<MoveCommand>(m_pQBertGO, DOWN_RIGHT));    // Right
}

void LevelComponent::SpawnDiscs()
{
    const int maxActiveDiscs = 2;
    int spawned = 0;

    for (auto const& tilePtr : m_pLevel->GetTiles())
    {
        if (tilePtr->GetType() != TileType::DISC) continue;
        if (spawned >= maxActiveDiscs) break;

        auto pos = GridToWorldDisc(tilePtr->GetGridPosition(), m_disc.tex.frameSize);

        auto discGO = GameObjectBuilder()
            .WithTranslation()
            .WithTexture(m_disc.tex.file, 0.f, 2.f)
            .WithAnimation(m_disc.tex.frameSize, m_disc.columns * m_disc.rows, 0.1f, m_disc.rows, m_disc.columns)
            .SetPosition(glm::vec3(pos.x, pos.y, 0.f))
            .Build();

        if (auto animComp = discGO->GetComponent<AnimationComponent>()) {
            int levelIdx = m_pLevel->GetLevelNumber() - 1;
            int startFrame = levelIdx * 5;
            int endFrame = startFrame + 4;
            animComp->SetFrame(startFrame);
            animComp->SetLoopRange(startFrame, endFrame);
            animComp->SetAutoAdvance(false);
        }

        auto pDisc = m_DiscGOs.emplace_back(discGO.get());
        if (auto scene = dae::SceneManager::GetInstance().GetActiveScene()) {
            scene->Add(std::move(discGO));
        }

        DiscManager::GetInstance().RegisterDisc(tilePtr->GetGridPosition(), pDisc);
        ++spawned;
    }
}



