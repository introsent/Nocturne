#pragma once
#include "Singleton.h"
#include <SDL.h>
#include <unordered_map>

namespace dae
{
    enum class InputState
    {
        Down,
        Up,
        Pressed
    };

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

    struct ControllerBinding
    {
        int button;
        InputState state;

        bool operator==(const ControllerBinding& other) const
        {
            return button == other.button && state == other.state;
        }
    };

    struct ControllerBindingHash
    {
        std::size_t operator()(const ControllerBinding& binding) const
        {
            return std::hash<int>()(binding.button) ^ (std::hash<int>()(static_cast<int>(binding.state)) << 1);
        }
    };

    class Command; 
    class InputManager final : public Singleton<InputManager>
    {
    public:
        bool ProcessInput();

        void BindCommand(SDL_Keycode key, InputState state, Command* command);

        void BindCommand(int controllerButton, InputState state, Command* command);

    private:
        std::unordered_map<KeyBinding, Command*, KeyBindingHash> m_KeyBindings;
        std::unordered_map<ControllerBinding, Command*, ControllerBindingHash> m_ControllerBindings;
    };
}

