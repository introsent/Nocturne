#pragma once
#include <memory>
#include <unordered_map>
#include <SDL.h>
#include "Command.h"
#include "InputState.h"
#include "Singleton.h"

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
        InputManager();
        ~InputManager() override;

        bool ProcessInput();  
        void BindKeyboardCommand(int key, InputState state, Command* command);
        void BindControllerCommand(unsigned int button, InputState state, Command* command);

    private:
        std::unordered_map<KeyBinding, Command*, KeyBindingHash> m_KeyBindings;
        std::unique_ptr<XInputImpl> m_pXInputImpl;
    };
}
