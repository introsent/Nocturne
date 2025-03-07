#include <Windows.h>
#include <XInput.h>
#include "InputManager.h"

#include <iostream>

#include "Command.h"
#include <SDL.h>
#include "backends/imgui_impl_sdl2.h"

bool dae::InputManager::ProcessInput()
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

    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    DWORD dwResult = XInputGetState(0, &state);
    if (dwResult == ERROR_SUCCESS)
    {
        for (auto& pair : m_ControllerBindings)
        {
            if ((pair.first.state == InputState::Down || pair.first.state == InputState::Pressed) &&
                (state.Gamepad.wButtons & pair.first.button))
            {
                pair.second->Execute();
            }
        }
    }

    return true;
}

void dae::InputManager::BindKeyboardCommand(SDL_Keycode key, InputState state, Command* command)
{
    KeyBinding binding{ key, state };
    m_KeyBindings[binding] = command;
}

void dae::InputManager::BindControllerCommand(int controllerButton, InputState state, Command* command)
{
    ControllerBinding binding{ controllerButton, state };
    m_ControllerBindings[binding] = command;
}
