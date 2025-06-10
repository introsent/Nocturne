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


void load()
{
	dae::SoundServiceLocator::Register(std::make_unique<dae::SoundService>());

    // 1) Create the Level1 scene
    auto& level1Scene = dae::SceneManager::GetInstance().CreateScene("Level1");
    dae::SceneManager::GetInstance().SetActiveScene("Level1");
    // Create background and logo objects.
    auto bg = GameObjectBuilder()
        .WithTexture("../Data/background.png", -2.f, 1.f)
        .SetPosition(glm::vec3(0.f, 0.f, 0.f))
        .Build();
    level1Scene.Add(std::move(bg));

    // 2) Add a LevelController GameObject which will spawn everything
    auto levelController = std::make_unique<dae::GameObject>();
    levelController->AddComponent<LevelComponent>(levelController.get(), 1);
    level1Scene.Add(std::move(levelController));


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


int main(int, char* []) {

    dae::Minigin engine("../Data/");
    engine.Run(load);

    return 0;
}


