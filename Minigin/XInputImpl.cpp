#include "XInputImpl.h"
#include <iostream> 
#include <SDL_syswm.h>

namespace dae
{
    XInputImpl::XInputImpl()
    {
        ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
    }

    bool XInputImpl::ProcessInput()
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        if (XInputGetState(0, &state) == ERROR_SUCCESS)
        {
            for (const auto& [button, commands] : m_ControllerCommands)
            {
                bool isPressed = (state.Gamepad.wButtons & button) != 0;
                bool wasPressed = (m_PreviousState.Gamepad.wButtons & button) != 0;

                for (const auto& [commandState, command] : commands)
                {
                    if ((commandState == InputState::Down && isPressed) ||
                        (commandState == InputState::Up && !isPressed && wasPressed) ||
                        (commandState == InputState::Pressed && isPressed && wasPressed))
                    {
                        command->Execute();
                    }
                }
            }
            m_PreviousState = state;
        }

        return true;
    }


    void XInputImpl::BindControllerCommand(unsigned int button, InputState state, Command* command)
    {
        m_ControllerCommands[button].emplace_back(state, command);
    }
}
