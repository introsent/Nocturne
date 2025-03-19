#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"

namespace dae
{
    InputManager::~InputManager() = default;

    bool InputManager::ProcessInput()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                return false;

            if (e.type == SDL_KEYDOWN)
            {
                KeyBinding binding{ e.key.keysym.sym, InputState::Down };
                auto it = m_KeyBindings.find(binding);
                if (it != m_KeyBindings.end())
                    it->second->Execute();
            }
            else if (e.type == SDL_KEYUP)
            {
                KeyBinding binding{ e.key.keysym.sym, InputState::Up };
                auto it = m_KeyBindings.find(binding);
                if (it != m_KeyBindings.end())
                    it->second->Execute();
            }

            // Process other SDL events (e.g. mouse events)

            // Process event for IMGUI
            ImGui_ImplSDL2_ProcessEvent(&e);
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        for (auto& pair : m_KeyBindings)
        {
            if (pair.first.state == InputState::Pressed)
            {
                SDL_Scancode scancode = SDL_GetScancodeFromKey(pair.first.key);
                if (currentKeyStates[scancode])
                {
                    pair.second->Execute();
                }
            }
        }
        return m_XInputManager.ProcessInput();  
    }

    void InputManager::BindKeyboardCommand(int key, InputState state, std::unique_ptr<Command> command)
    {
        KeyBinding binding{ key, state };
        m_KeyBindings[binding] = std::move(command);
    }

    void InputManager::BindControllerCommand(unsigned int button, InputState state, std::unique_ptr<Command> command) const
    {
        m_XInputManager.BindControllerCommand(button, state, std::move(command));
    }
}
