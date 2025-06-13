#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "Minigin.h"
#include "CharacterFactory.h"
#include "GameObjectBuilder.h"
#include "InputManager.h"
#include "InputState.h"
#include "KillCommand.h"
#include "LevelComponent.h"
#include "LivesDisplayObserver.h"
#include "MoveCommand.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreCommand.h"
#include "ScoreDisplayObserver.h"
#include "SoundService.h"
#include "SoundServiceLocator.h"
#include "TestSoundCommand.h"
#include "UIFactory.h"
#include "LevelManagerComponent.h"

#include <filesystem>
#include <iostream>
#include "MenuCommands.h"
#include "MenuComponent.h"


void CreateGameScene()
{
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    dae::SoundServiceLocator::Register(std::make_unique<dae::SoundService>());
    dae::SoundServiceLocator::GetService()->RegisterSound("qbert_jump",         "../Data/Sounds/QBert Jump.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("qbert_hit",          "../Data/Sounds/Qbert Hit.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("qbert_fall",         "../Data/Sounds/QBert Fall.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("round_complete",     "../Data/Sounds/Round Complete Tune.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("swearing",           "../Data/Sounds/Swearing.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("coily_snake_jump",   "../Data/Sounds/Coily Snake Jump.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("coily_egg_jump",     "../Data/Sounds/Coily Egg Jump.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("coily_fall",         "../Data/Sounds/Coily Fall.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("others_jump",        "../Data/Sounds/Other Foes Jump.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("disk_lift",          "../Data/Sounds/Disk Lift.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("disk_land",          "../Data/Sounds/Disk Land.wav");
    dae::SoundServiceLocator::GetService()->RegisterSound("slick_sam_caught",   "../Data/Sounds/SlickSam Caught.wav");

    auto& scene = dae::SceneManager::GetInstance().CreateScene("Main");
    dae::SceneManager::GetInstance().SetActiveScene("Main");

    // Background
    auto bg = GameObjectBuilder()
        .WithTexture("background.png", -2.f, 1.f)
        .SetPosition(glm::vec3(0.f, 0.f, 0.f))
        .Build();
    scene.Add(std::move(bg));

    auto playerDataObj = std::make_unique<dae::GameObject>();
    auto playerData = playerDataObj->AddComponent<PlayerDataComponent>(playerDataObj.get());
    scene.Add(std::move(playerDataObj));

    // Create persistent Level Manager
    auto manager = std::make_unique<dae::GameObject>();
    auto levelManager = manager->AddComponent<LevelManagerComponent>(manager.get(), playerData);

    levelManager->OnAllLevelsCompleted.Subscribe([]() {
        // Handle game completion
        std::cout << "All levels completed! You win!\n";
        });

    scene.Add(std::move(manager));



    // Create UI displays
    auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 36);
    auto scoreText = CreateUIText("Score: 0", font, glm::vec3(10, 10, 0));
    auto scoreObserver = scoreText->AddComponent<ScoreDisplayObserver>(
        scoreText.get(),
        scoreText->GetComponent<dae::TextComponent>()
    );
    scoreObserver->Register(playerData->GetScore());

    scene.Add(std::move(scoreText));

    auto livesText = CreateUIText("Lives: 3", font, glm::vec3(10, 50, 0));
    auto livesObserver = livesText->AddComponent<LivesDisplayObserver>(
        livesText.get(),
        livesText->GetComponent<dae::TextComponent>()
    );
    livesObserver->Register(playerData->GetHealth());

    scene.Add(std::move(livesText));
}


void CreateMenuScene()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Menu");
    dae::SceneManager::GetInstance().SetActiveScene("Menu");

    // Background
    auto bg = GameObjectBuilder()
        .WithTexture("background.png", -2.f, 1.f)
        .SetPosition(glm::vec3(0.f, 0.f, 0.f))
        .Build();
    scene.Add(std::move(bg));

    // Title
    auto font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 72);
    auto title = CreateUIText("QBERT", font, glm::vec3(175, 100, 0));
    scene.Add(std::move(title));

    // Menu Items
    font = dae::ResourceManager::GetInstance().LoadFont("Minecraft.ttf", 36);
    auto soloText = CreateUIText("Solo Mode", font, glm::vec3(220, 250, 0));
    auto coopText = CreateUIText("Co-op Mode", font, glm::vec3(220, 320, 0));
    auto versusText = CreateUIText("Versus Mode", font, glm::vec3(220, 390, 0));

    // Selection Arrow
    auto arrow = GameObjectBuilder()
        .WithTexture("Selection Arrow.png", 0.f, 3.f)
        .SetPosition(glm::vec3(270, 250, 0))
        .Build();

    // Menu Controller
    auto menuController = std::make_unique<dae::GameObject>();
    auto menuComp = menuController->AddComponent<MenuComponent>(menuController.get());

    // Store pointers before moving
    auto* soloPtr = soloText.get();
    auto* coopPtr = coopText.get();
    auto* versusPtr = versusText.get();

    menuComp->SetMenuItems({ soloPtr, coopPtr, versusPtr });
    menuComp->SetArrow(arrow.get());

    menuComp->AddMenuItem("Solo", []() {
        CreateGameScene();
        dae::SceneManager::GetInstance().SetActiveScene("Main");
        });

    menuComp->AddMenuItem("Co-op", []() {
        std::cout << "Co-op mode selected\n";
        // Implement co-op mode
        });

    menuComp->AddMenuItem("Versus", []() {
        std::cout << "Versus mode selected\n";
        // Implement versus mode
        });

    // Add objects to scene
    scene.Add(std::move(soloText));
    scene.Add(std::move(coopText));
    scene.Add(std::move(versusText));
    scene.Add(std::move(arrow));
    scene.Add(std::move(menuController));

    // Bind menu navigation commands
    dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, InputState::Down,
        std::make_unique<MenuSelectCommand>(true));
    dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, InputState::Down,
        std::make_unique<MenuSelectCommand>(false));
    dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_RETURN, InputState::Down,
        std::make_unique<MenuActivateCommand>());

    dae::InputManager::GetInstance().BindControllerCommand(
        dae::XInputManager::GetXInputValue(GamepadButton::DpadUp),
        InputState::Down,
        std::make_unique<MenuSelectCommand>(true));

    dae::InputManager::GetInstance().BindControllerCommand(
        dae::XInputManager::GetXInputValue(GamepadButton::DpadDown),
        InputState::Down,
        std::make_unique<MenuSelectCommand>(false));

    dae::InputManager::GetInstance().BindControllerCommand(
        dae::XInputManager::GetXInputValue(GamepadButton::South),
        InputState::Down,
        std::make_unique<MenuActivateCommand>());
}

int main(int, char* []) {

    dae::Minigin engine("../Data/");
    CreateMenuScene();
    engine.Run();

    return 0;
}


