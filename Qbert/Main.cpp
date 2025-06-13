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



    //// Bind WASD for char1 (keyboard)
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char1.get(), speed1, glm::vec2(0.f, -1.f))); // Up
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char1.get(), speed1, glm::vec2(0.f, 1.f)));  // Down
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char1.get(), speed1, glm::vec2(-1.f, 0.f))); // Left
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char1.get(), speed1, glm::vec2(1.f, 0.f)));  // Right
    



    // 3) Tell the engine to start on this scene
   

    //// Load initial sounds
    //auto* sound_service = dae::SoundServiceLocator::GetService();
    //sound_service->LoadSound("test", "../Data/coily_snake.wav");
    //
    //
    //auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
    //
    //// Create background and logo objects.
    //auto bg = GameObjectBuilder()
    //    .WithTexture("background.tga")
    //    .SetPosition(glm::vec3(0.f, 0.f, 0.f))
    //    .Build();
    //scene.Add(bg);
    //
    //auto logo = GameObjectBuilder()
    //    .WithTexture("logo.tga")
    //    .SetPosition(glm::vec3(216.f, 180.f, 0.f))
    //    .Build();
    //scene.Add(logo);
    //
    //// Load fonts.
    //auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    //auto fontInfo = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
    //
    //// Create UI text elements.
    //auto title = CreateUIText("Programming 4 Assignment", font, glm::vec3(80.f, 50.f, 0.f));
    //scene.Add(title);
    //
    //auto info1 = CreateUIText("Use WASD to move Qbert, C to inflict damage, Z and X to pick up pellets", fontInfo, glm::vec3(0.f, 100.f, 0.f));
    //scene.Add(info1);
    //
    //auto info2 = CreateUIText("Use D-Pad to move Slick Sam, X to inflict damage, A and B to pick up pellets", fontInfo, glm::vec3(0.f, 120.f, 0.f));
    //scene.Add(info2);
    //
    //auto info3 = CreateUIText("Use Y on gamepad or V on keyboard to play a sound", fontInfo, glm::vec3(0.f, 140.f, 0.f));
    //scene.Add(info3);
    //
    //auto fpsText = GameObjectBuilder()
    //    .WithText("FPS", font)
    //    .WithFPS()
    //    .SetPosition(glm::vec3(0.f, 0.f, 0.f))
    //    .Build();
    //scene.Add(fpsText);
    //
    //// Create characters using the factory function.
    //dae::HealthComponent* healthComponentChar1 = nullptr;
    //dae::ScoreComponent* scoreComponentChar1 = nullptr;
    //auto char1 = CreateCharacter("qbert_week2.tga", glm::vec3(200.f, 300.f, 0.f),
    //    &healthComponentChar1, &scoreComponentChar1);
    //scene.Add(char1);
    //
    //dae::HealthComponent* healthComponentChar2 = nullptr;
    //dae::ScoreComponent* scoreComponentChar2 = nullptr;
    //auto char2 = CreateCharacter("slick_sam.tga", glm::vec3(200.f, 400.f, 0.f),
    //    &healthComponentChar2, &scoreComponentChar2);
    //scene.Add(char2);
    //
    //// Create UI elements for character health and score.
    //auto textObjChar1 = CreateUIText("Remaining Lives: 3", fontInfo, glm::vec3(0.f, 200.f, 0.f));
    //// Assuming GetComponent<T>() exists to retrieve the text component
    //auto textComponentChar1 = textObjChar1->GetComponent<dae::TextComponent>();
    //auto livesObserver1 = textObjChar1->AddComponent<dae::LivesDisplayObserver>(textObjChar1.get(), textComponentChar1);
    //livesObserver1->Register(healthComponentChar1);
    //scene.Add(textObjChar1);
    //
    //auto textObjChar2 = CreateUIText("Remaining Lives: 3", fontInfo, glm::vec3(0.f, 250.f, 0.f));
    //auto textComponentChar2 = textObjChar2->GetComponent<dae::TextComponent>();
    //auto livesObserver2 = textObjChar2->AddComponent<dae::LivesDisplayObserver>(textObjChar2.get(), textComponentChar2);
    //livesObserver2->Register(healthComponentChar2);
    //scene.Add(textObjChar2);
    //
    //auto textObjScoreChar1 = CreateUIText("Score: 0", fontInfo, glm::vec3(0.f, 220.f, 0.f));
    //auto textComponentScoreChar1 = textObjScoreChar1->GetComponent<dae::TextComponent>();
    //auto scoreObserver1 = textObjScoreChar1->AddComponent<dae::ScoreDisplayObserver>(textObjScoreChar1.get(), textComponentScoreChar1);
    //scoreObserver1->Register(scoreComponentChar1);
    //scene.Add(textObjScoreChar1);
    //
    //auto textObjScoreChar2 = CreateUIText("Score: 0", fontInfo, glm::vec3(0.f, 270.f, 0.f));
    //auto textComponentScoreChar2 = textObjScoreChar2->GetComponent<dae::TextComponent>();
    //auto scoreObserver2 = textObjScoreChar2->AddComponent<dae::ScoreDisplayObserver>(textObjScoreChar2.get(), textComponentScoreChar2);
    //scoreObserver2->Register(scoreComponentChar2);
    //scene.Add(textObjScoreChar2);
    //
    //// Bind commands to inputs as in your original code.
    //float speed1 = 1.0f;
    //float speed2 = speed1 * 2.0f;
    //
    //// Bind WASD for char1 (keyboard)
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char1.get(), speed1, glm::vec2(0.f, -1.f))); // Up
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char1.get(), speed1, glm::vec2(0.f, 1.f)));  // Down
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char1.get(), speed1, glm::vec2(-1.f, 0.f))); // Left
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char1.get(), speed1, glm::vec2(1.f, 0.f)));  // Right
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_c, InputState::Down,
    //    std::make_unique<dae::KillCommand>(char1.get()));
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_z, InputState::Down,
    //    std::make_unique<dae::ScoreCommand>(char1.get(), 10));
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_x, InputState::Down,
    //    std::make_unique<dae::ScoreCommand>(char1.get(), 100));
    //
    //dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_v, InputState::Down,
    //    std::make_unique<dae::TestSoundCommand>());
    //
    //
    //dae::XInputManager m_XInputManager;
    //// Bind D-Pad for char2 (controller)
    //dae::InputManager::GetInstance().BindControllerCommand(m_XInputManager.GetXInputValue(GamepadButton::DpadUp), InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char2.get(), speed2, glm::vec2(0.f, -1.f)));   // Up
    //dae::InputManager::GetInstance().BindControllerCommand(m_XInputManager.GetXInputValue(GamepadButton::DpadDown), InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char2.get(), speed2, glm::vec2(0.f, 1.f)));    // Down
    //dae::InputManager::GetInstance().BindControllerCommand(m_XInputManager.GetXInputValue(GamepadButton::DpadLeft), InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char2.get(), speed2, glm::vec2(-1.f, 0.f)));   // Left
    //dae::InputManager::GetInstance().BindControllerCommand(m_XInputManager.GetXInputValue(GamepadButton::DpadRight), InputState::Pressed,
    //    std::make_unique<dae::MoveCommand>(char2.get(), speed2, glm::vec2(1.f, 0.f)));    // Right
    //
    //dae::InputManager::GetInstance().BindControllerCommand(m_XInputManager.GetXInputValue(GamepadButton::West), InputState::Up,
    //    std::make_unique<dae::KillCommand>(char2.get()));
    //dae::InputManager::GetInstance().BindControllerCommand(m_XInputManager.GetXInputValue(GamepadButton::South), InputState::Up,
    //    std::make_unique<dae::ScoreCommand>(char2.get(), 10));
    //dae::InputManager::GetInstance().BindControllerCommand(m_XInputManager.GetXInputValue(GamepadButton::East), InputState::Up,
    //    std::make_unique<dae::ScoreCommand>(char2.get(), 100));
    //
    //dae::InputManager::GetInstance().BindControllerCommand(m_XInputManager.GetXInputValue(GamepadButton::North), InputState::Up,
    //    std::make_unique<dae::TestSoundCommand>());
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
        InputState::Pressed,
        std::make_unique<MenuSelectCommand>(true));

    dae::InputManager::GetInstance().BindControllerCommand(
        dae::XInputManager::GetXInputValue(GamepadButton::DpadDown),
        InputState::Pressed,
        std::make_unique<MenuSelectCommand>(false));

    dae::InputManager::GetInstance().BindControllerCommand(
        dae::XInputManager::GetXInputValue(GamepadButton::South),
        InputState::Pressed,
        std::make_unique<MenuActivateCommand>());
}

int main(int, char* []) {

    dae::Minigin engine("../Data/");
    CreateMenuScene();
    engine.Run();

    return 0;
}


