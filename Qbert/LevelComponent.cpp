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

LevelComponent::LevelComponent(dae::GameObject* owner, int levelIndex)
    : Component(owner)
    , m_pLevel(std::make_unique<Level>(levelIndex))
{
    SpawnTiles();
	SpawnQBert();
    m_pLevel->OnTileColored.Subscribe([this](const Tile& tile) { OnTileColored(tile); });
}

void LevelComponent::Update(float) {}


void LevelComponent::SpawnTiles() {
    auto texture = dae::ResourceManager::GetInstance().LoadTexture(TileAtlasFile);
    const int levelNumber = m_pLevel->GetLevelNumber();
    const int levelColumn = levelNumber - 1; // Convert to 0-based column index

    for (auto const& tilePtr : m_pLevel->GetTiles()) {
        const Tile& tile = *tilePtr;

        auto tileGO = std::make_shared<dae::GameObject>();

        // Position setup
        glm::vec2 worldPos = GridToWorld(tile.GetGridPosition());
        tileGO->AddComponent<dae::TranslationComponent>(tileGO.get())
            ->Translate(glm::vec3(worldPos.x, worldPos.y, -tile.GetGridPosition().y));

        // Texture and animation setup
        auto textureComp = tileGO->AddComponent<dae::TextureComponent>(tileGO.get(), TileAtlasFile, 2.f);

        auto animationComp = tileGO->AddComponent<AnimationComponent>(
            tileGO.get(),
            textureComp,
            MapFrameSize,       // 32x32 per frame
            18,              // Total frames (6 columns * 3 rows)
            0.f,             // No auto-advance
            3,               // Rows (states)
            6                // Columns (levels)
        );

        // Calculate frame: (state_row * 6) + level_column
        const int stateRow = tile.GetColorIndex();
        const int frame = stateRow * 6 + levelColumn;
        animationComp->SetFrame(frame);

        // Add to scene
        m_TileGOs.push_back(tileGO);
        if (auto scene = dae::SceneManager::GetInstance().GetActiveScene()) {
            scene->Add(tileGO);
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
void LevelComponent::SpawnQBert() {
    auto qbertGO = std::make_shared<dae::GameObject>();
    auto startTile = m_pLevel->GetTileAt({ 0, 0 });

    glm::vec2 worldPos = GridToWorldCharacter(startTile->GetGridPosition());
    //auto translation = qbertGO->AddComponent<dae::TranslationComponent>(qbertGO.get());
    //translation->Translate(glm::vec3(worldPos.x, worldPos.y, 0.f));

    auto textureComp = qbertGO->AddComponent<dae::TextureComponent>(qbertGO.get(), QbertFile, 2.f);
    auto animationComp = qbertGO->AddComponent<AnimationComponent>(
        qbertGO.get(),
        textureComp,
        QbertFrameSize, // Frame size
        4,              // Total frames
        0.2f,           // Time per frame
        1,              // Rows
        4               // Columns
    );
    animationComp->SetFrame(3);

    qbertGO->AddComponent<QBertPlayer>(qbertGO.get(), m_pLevel.get());

    m_pQBertGO = qbertGO;
    dae::SceneManager::GetInstance().GetActiveScene()->Add(qbertGO);

    BindCommands();
}

void LevelComponent::BindCommands() const
{
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, InputState::Up,
		std::make_unique<MoveCommand>(m_pQBertGO.get(), UP_RIGHT));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, InputState::Up,
		std::make_unique<MoveCommand>(m_pQBertGO.get(), DOWN_LEFT));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, InputState::Up,
		std::make_unique<MoveCommand>(m_pQBertGO.get(),UP_LEFT));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, InputState::Up,
		std::make_unique<MoveCommand>(m_pQBertGO.get(),  DOWN_RIGHT));


    dae::InputManager::GetInstance().BindControllerCommand(dae::XInputManager::GetXInputValue(GamepadButton::DpadUp), InputState::Pressed,
                                                           std::make_unique<MoveCommand>(m_pQBertGO.get(), UP_RIGHT));   // Up
    dae::InputManager::GetInstance().BindControllerCommand(dae::XInputManager::GetXInputValue(GamepadButton::DpadDown), InputState::Pressed,
                                                           std::make_unique<MoveCommand>(m_pQBertGO.get(), DOWN_LEFT));    // Down
    dae::InputManager::GetInstance().BindControllerCommand(dae::XInputManager::GetXInputValue(GamepadButton::DpadLeft), InputState::Pressed,
                                                           std::make_unique<MoveCommand>(m_pQBertGO.get(), UP_LEFT));   // Left
    dae::InputManager::GetInstance().BindControllerCommand(dae::XInputManager::GetXInputValue(GamepadButton::DpadRight), InputState::Pressed,
                                                           std::make_unique<MoveCommand>(m_pQBertGO.get(), DOWN_RIGHT));    // Right
}

//void LevelComponent::SpawnDiscs() {
//    dae::ResourceManager::GetInstance().LoadTexture("Disc.png");
//
//    for (const auto& pos : { glm::vec2{200.f, 300.f}, glm::vec2{600.f, 300.f} }) {
//        auto discGO = std::make_shared<dae::GameObject>();
//        discGO->AddComponent<dae::TranslationComponent>(discGO.get())
//            ->Translate(glm::vec3(pos.x, pos.y, 0.f));
//
//        discGO->AddComponent<dae::TextureComponent>(discGO.get(), "Disc.png");
//        m_DiscGOs.push_back(discGO);
//        dae::SceneManager::GetInstance().GetActiveScene()->Add(discGO);
//    }
//}