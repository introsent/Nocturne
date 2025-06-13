#pragma once
#include <memory>
#include <unordered_map>
#include <SDL.h>
#include "Command.h"
#include "InputState.h"
#include "Singleton.h"
#include "XInputManager.h"

namespace dae
{
    struct KeyBinding
    {
        SDL_Keycode key;
        InputState state;

        bool operator==(const KeyBinding& other) const
        {
            return key == other.key && state == other.state;
        }
    };

    struct KeyBindingHash
    {
        std::size_t operator()(const KeyBinding& binding) const
        {
            return std::hash<int>()(static_cast<int>(binding.key)) ^ (std::hash<int>()(static_cast<int>(binding.state)) << 1);
        }
    };

    class XInputImpl;
    class InputManager final : public Singleton<InputManager>
    {
    public:
        InputManager() = default;
        ~InputManager() override;

        InputManager(const InputManager& other) = delete;
        InputManager& operator=(const InputManager& other) = delete;
        InputManager(InputManager&& other) noexcept = delete;
        InputManager& operator=(InputManager&& other) noexcept = delete;

        bool ProcessInput();
        void BindKeyboardCommand(int key, InputState state, std::unique_ptr<Command> command);
        void BindControllerCommand(int controllerIndex, unsigned int button, InputState state, std::unique_ptr<Command> command);

    private:
        std::unordered_map<KeyBinding, std::unique_ptr<Command>, KeyBindingHash> m_KeyBindings;
        XInputManager m_XInputManager;
    };
}