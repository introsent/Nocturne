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
        void BindKeyboardCommand(int key, InputState state, Command* command);
        void BindControllerCommand(unsigned int button, InputState state, Command* command) const;

    private:
        std::unordered_map<KeyBinding, Command*, KeyBindingHash> m_KeyBindings;
        XInputManager m_XInputManager;
    };
}
