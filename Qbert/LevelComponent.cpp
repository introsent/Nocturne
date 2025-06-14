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
#include <SoundServiceLocator.h>
#include "MultiQbertPositionProxy.h"

LevelComponent::LevelComponent(dae::GameObject* owner, int levelIndex, int stageIndex, PlayerDataComponent* playerData, GameMode mode)
    : Component(owner), m_pLevel(std::make_unique<Level>(levelIndex, stageIndex)), m_LevelIndex(levelIndex), m_StageIndex(stageIndex), m_pPlayerData(playerData), m_Mode(mode)
{
    auto levels = LevelDataLoader::LoadLevels(levelDataPath);
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
    SpawnPlayers();

    m_pLevel->OnTileColored.Subscribe([this](const Tile& tile) { OnTileColored(tile); });
    m_pLevel->OnLevelCompleted.Subscribe([this]() { OnLevelCompleted(); });
}

void LevelComponent::SetPlayerData(PlayerDataComponent* playerData)
{
    m_pPlayerData = playerData;
}

void LevelComponent::Update(float deltaTime) {
    if (m_IsEndingAnimationPlaying) {
        PlayEndingAnimation(deltaTime);
        return;
    }

    if (m_LevelCompleted) return;

    m_AccumulatedTime += deltaTime;

    std::vector<EnemySpawnData> enemiesToSpawn;
    for (auto it = m_StageEnemies.begin(); it != m_StageEnemies.end(); ) {
        if (m_AccumulatedTime >= it->spawn_time) {
            if (it->type == "Coily" && m_Mode == GameMode::Versus) {
                ++it;
                continue;
            }
            enemiesToSpawn.push_back(*it);
            it = m_StageEnemies.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto& spawnInfo : enemiesToSpawn) {
        if (m_LevelCompleted) break;

        auto enemyGO = m_enemyPrefabs->CreateEnemy(
            spawnInfo.type,
            m_pLevel.get(),
            spawnInfo.start_position,
            *m_pQbertPositionProxy
        );

        enemyGO->GetComponent<Enemy>()->SetScoreComponent(
            m_pPlayerData ? m_pPlayerData->GetScore() : nullptr
        );

        enemyGO->GetComponent<Enemy>()->OnCollisionWithQbert.Subscribe([this](dae::GameObject* enemy) {
                OnCollisionWithQbert(enemy);
        });

        

        enemyGO->SetParent(GetOwner());
        if (auto scene = dae::SceneManager::GetInstance().GetActiveScene()) {
            dae::SceneManager::GetInstance().GetActiveScene()->Add(std::move(enemyGO));
        }
    }

    if (m_Mode == GameMode::Versus)
    {
        if (m_CoilyGO->IsMarkedForDestroy())
        {
            m_CoilyGO = SpawnPlayerCoily();
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

        tileGO->SetParent(GetOwner());
        if (auto animationComp = tileGO->GetComponent<AnimationComponent>()) {
            animationComp->SetFrame(CalculateTileFrame(tile));
        }

        m_TileGOs.emplace_back(tileGO.get());
        if (auto scene = dae::SceneManager::GetInstance().GetActiveScene()) {
            scene->Add(std::move(tileGO));
        }
    }
}

void LevelComponent::OnTileColored(const Tile& tile) const
{
    for (auto& tileGO : m_TileGOs) {
        const glm::vec2 currentPos = {
            tileGO->GetWorldPosition().x,
            tileGO->GetWorldPosition().y
        };

        if (currentPos == GridToWorld(tile.GetGridPosition())) {
            if (auto animComp = tileGO->GetComponent<AnimationComponent>()) {
                animComp->SetFrame(CalculateTileFrame(tile));
            }
            break;
        }
    }
    if (m_pPlayerData && m_pPlayerData->GetScore()) {
        m_pPlayerData->GetScore()->AddScore(25);
    }
}

int LevelComponent::CalculateTileFrame(const Tile& tile) const
{
    const int stateRow = tile.GetColorIndex();
    const int levelColumn = (m_pLevel->GetLevelNumber() - 1) + (m_pLevel->GetStageNumber() - 1);
    return (stateRow * 6) + levelColumn;
}

void LevelComponent::OnLevelCompleted()
{
    if (m_LevelCompleted) return;
    m_LevelCompleted = true;
    m_IsEndingAnimationPlaying = true;
    m_AnimationTotalTime = 0.0f;
    m_AnimationStateTime = 0.0f;
    m_CurrentAnimationState = 0;

    dae::SoundServiceLocator::GetService()->PlaySound("round_complete");

    if (m_pPlayerData && m_pPlayerData->GetScore()) {
        int remainingDiscs = DiscManager::GetInstance().GetRemainingDiscs();
        m_pPlayerData->GetScore()->AddScore(remainingDiscs * 50);
    }

    UpdateAllTilesToAnimationState();
}

void LevelComponent::SpawnPlayers() {
    if (m_Mode == GameMode::Solo) {
        auto qbert = SpawnQBertAt({ 0, 0 }, InputDevice::Keyboard, false);
        m_QbertGOs.push_back(qbert);
        SetupQbertPositionProxy();
    }
    else if (m_Mode == GameMode::Coop) {
        int rows = m_pLevel->GetRows();
        auto qbert1 = SpawnQBertAt({ 0, rows - 1 }, InputDevice::Keyboard, false);
        auto qbert2 = SpawnQBertAt({ rows - 1, rows - 1 }, InputDevice::Controller1, true);
        m_QbertGOs.push_back(qbert1);
        m_QbertGOs.push_back(qbert2);
        SetupQbertPositionProxy();
    }
    else if (m_Mode == GameMode::Versus) {
        auto qbert = SpawnQBertAt({ 0, 0 }, InputDevice::Keyboard, false);
        m_QbertGOs.push_back(qbert);
        SetupQbertPositionProxy();
        m_CoilyGO = SpawnPlayerCoily();
    }

    BindCommands(); 
}

void LevelComponent::SetupQbertPositionProxy()
{
    if (!m_QbertGOs.empty()) {
        auto multiProxy = std::make_unique<MultiQbertPositionProxy>();
        for (auto* qbertGO : m_QbertGOs) {
            auto player = qbertGO->GetComponent<QBertPlayer>();
            auto proxy = std::make_shared<QbertPositionProxy>(player);
            multiProxy->AddProxy(proxy);

            player->OnPositionChanged.Subscribe([proxy](const glm::ivec2& newPos) {
                proxy->UpdatePosition(newPos);
                });
        }
        m_pQbertPositionProxy = std::move(multiProxy);
    }
}

void LevelComponent::OnCollisionWithQbert(dae::GameObject* enemy)
{
    if (enemy->GetComponent<Enemy>()->ShouldDamageQBert())
    {
        for (auto* qbertGO : m_QbertGOs) {
            if (enemy->GetComponent<Enemy>()->AreEnemyAndQbertClose(enemy->GetWorldPosition(), qbertGO->GetWorldPosition()))
            {
                if (qbertGO->GetComponent<QBertPlayer>()->TakeHit()) {
                    enemy->MarkForDestroy();
                }
            }
        }
    }
    else
    {
        m_pPlayerData->GetScore()->AddScore(300);
        dae::SoundServiceLocator::GetService()->PlaySound("slick_sam_caught");
        enemy->MarkForDestroy();
    }
}


dae::GameObject* LevelComponent::SpawnQBertAt(const glm::ivec2& gridPos, InputDevice, bool isSecondPLayer) {
    glm::vec2 worldPos = GridToWorldCharacter(gridPos);

    auto qbertGO = GameObjectBuilder()
        .WithTranslation()
        .WithTexture(isSecondPLayer ? m_qbert2.tex.file : m_qbert.tex.file , 0.f, 2.f)
        .WithAnimation(m_qbert.tex.frameSize, m_qbert.columns * m_qbert.rows, 0.2f, m_qbert.rows, m_qbert.columns)
        .WithComponent<QBertPlayer>(m_pLevel.get(), m_pPlayerData->GetHealth(), gridPos)
        .SetPosition(glm::vec3(worldPos.x, worldPos.y, 0.f))
        .Build();

    qbertGO->SetParent(GetOwner());

	dae::GameObject* qbertGOPtr = qbertGO.get();

    if (auto animationComp = qbertGO->GetComponent<AnimationComponent>()) {
        animationComp->SetFrame(3);
    }

    if (auto scene = dae::SceneManager::GetInstance().GetActiveScene()) {
        scene->Add(std::move(qbertGO));
    }

    return qbertGOPtr;
}

dae::GameObject* LevelComponent::SpawnPlayerCoily() {
    auto coilyGO = m_enemyPrefabs->CreateEnemy("Coily", m_pLevel.get(), { 0, 0 }, *m_pQbertPositionProxy);
    coilyGO->GetComponent<Coily>()->SetPlayerControlled(true);
    coilyGO->SetParent(GetOwner());
    coilyGO->GetComponent<Enemy>()->SetScoreComponent(
        m_pPlayerData ? m_pPlayerData->GetScore() : nullptr
    );

    coilyGO->GetComponent<Coily>()->OnCollisionWithQbert.Subscribe([this](dae::GameObject* enemy) {
        OnCollisionWithQbert(enemy);
            });
	dae::GameObject* coilyGOPtr = coilyGO.get();
    if (auto scene = dae::SceneManager::GetInstance().GetActiveScene()) {
        scene->Add(std::move(coilyGO));
    }
    return coilyGOPtr;
}

void LevelComponent::BindCommands() {
    if (m_Mode == GameMode::Solo) {
        BindQBertInputs(m_QbertGOs[0], InputDevice::Keyboard);
        BindQBertInputs(m_QbertGOs[0], InputDevice::Controller0);
    }
    else if (m_Mode == GameMode::Coop) {
        BindQBertInputs(m_QbertGOs[1], InputDevice::Keyboard);
        BindQBertInputs(m_QbertGOs[0], InputDevice::Controller0);
        BindQBertInputs(m_QbertGOs[1], InputDevice::Controller1);
    }
    else if (m_Mode == GameMode::Versus) {
        BindQBertInputs(m_QbertGOs[0], InputDevice::Keyboard);
        BindQBertInputs(m_QbertGOs[0], InputDevice::Controller0);
        BindCoilyInputs(m_CoilyGO, InputDevice::Controller1);
    }
}

void LevelComponent::BindQBertInputs(dae::GameObject* qbertGO, InputDevice device) {
    if (device == InputDevice::Keyboard) {
        dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, InputState::Down, std::make_unique<MoveCommand>(qbertGO, UP_RIGHT));
        dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, InputState::Down, std::make_unique<MoveCommand>(qbertGO, DOWN_LEFT));
        dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, InputState::Down, std::make_unique<MoveCommand>(qbertGO, UP_LEFT));
        dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, InputState::Down, std::make_unique<MoveCommand>(qbertGO, DOWN_RIGHT));
    }
    else {
        int controllerIdx = (device == InputDevice::Controller0) ? 0 : 1;
        dae::InputManager::GetInstance().BindControllerCommand(controllerIdx, dae::XInputManager::GetXInputValue(GamepadButton::DpadUp), InputState::Down, std::make_unique<MoveCommand>(qbertGO, UP_RIGHT));
        dae::InputManager::GetInstance().BindControllerCommand(controllerIdx, dae::XInputManager::GetXInputValue(GamepadButton::DpadDown), InputState::Down, std::make_unique<MoveCommand>(qbertGO, DOWN_LEFT));
        dae::InputManager::GetInstance().BindControllerCommand(controllerIdx, dae::XInputManager::GetXInputValue(GamepadButton::DpadLeft), InputState::Down, std::make_unique<MoveCommand>(qbertGO, UP_LEFT));
        dae::InputManager::GetInstance().BindControllerCommand(controllerIdx, dae::XInputManager::GetXInputValue(GamepadButton::DpadRight), InputState::Down, std::make_unique<MoveCommand>(qbertGO, DOWN_RIGHT));
    }
}

void LevelComponent::BindCoilyInputs(dae::GameObject* coilyGO, InputDevice device) {
    int controllerIdx = (device == InputDevice::Controller0) ? 0 : 1;
    dae::InputManager::GetInstance().BindControllerCommand(controllerIdx, dae::XInputManager::GetXInputValue(GamepadButton::DpadUp), InputState::Down, std::make_unique<MoveCommand>(coilyGO, UP_RIGHT));
    dae::InputManager::GetInstance().BindControllerCommand(controllerIdx, dae::XInputManager::GetXInputValue(GamepadButton::DpadDown), InputState::Down, std::make_unique<MoveCommand>(coilyGO, DOWN_LEFT));
    dae::InputManager::GetInstance().BindControllerCommand(controllerIdx, dae::XInputManager::GetXInputValue(GamepadButton::DpadLeft), InputState::Down, std::make_unique<MoveCommand>(coilyGO, UP_LEFT));
    dae::InputManager::GetInstance().BindControllerCommand(controllerIdx, dae::XInputManager::GetXInputValue(GamepadButton::DpadRight), InputState::Down, std::make_unique<MoveCommand>(coilyGO, DOWN_RIGHT));
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

        discGO->SetParent(GetOwner());

        auto pDisc = m_DiscGOs.emplace_back(discGO.get());

        if (auto scene = dae::SceneManager::GetInstance().GetActiveScene()) {
            scene->Add(std::move(discGO));
        }

        DiscManager::GetInstance().RegisterDisc(tilePtr->GetGridPosition(), pDisc);
        ++spawned;
    }
}

void LevelComponent::PlayEndingAnimation(float deltaTime) {
    m_AnimationTotalTime += deltaTime;
    m_AnimationStateTime += deltaTime;

    if (m_AnimationStateTime >= 0.2f) {
        m_AnimationStateTime = 0.0f;
        m_CurrentAnimationState = (m_CurrentAnimationState + 1) % MAX_ANIMATION_STATES;
        UpdateAllTilesToAnimationState();
    }

    if (m_AnimationTotalTime >= 3.0f) {
        m_IsEndingAnimationPlaying = false;
        OnLevelCompletedEvent.Invoke();
    }
}

void LevelComponent::UpdateAllTilesToAnimationState() {
    const int levelColumn = (m_LevelIndex - 1) + (m_StageIndex - 1);

    for (auto& tileGO : m_TileGOs) {
        if (auto animComp = tileGO->GetComponent<AnimationComponent>()) {
            int frame = (m_CurrentAnimationState * 6) + levelColumn;
            animComp->SetFrame(frame);
        }
    }
}

