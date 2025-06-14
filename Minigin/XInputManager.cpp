#include "XInputManager.h"

#include <SDL_syswm.h>
#include <unordered_map>
#include <XInput.h>

namespace dae
{
    class XInputManager::XInputImpl
    {
    public:
        bool ProcessInput();
        void BindControllerCommand(int controllerIndex, unsigned int button, InputState state, std::unique_ptr<Command> command);
        void ResetControllerStates();

    private:
        std::unordered_map<int, std::unordered_map<unsigned int, std::unordered_map<InputState, std::unique_ptr<Command>>>> m_ControllerCommands;
        std::unordered_map<int, XINPUT_STATE> m_PreviousStates;
    };

    bool XInputManager::XInputImpl::ProcessInput()
    {
        for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
            XINPUT_STATE state;
            ZeroMemory(&state, sizeof(XINPUT_STATE));

            if (XInputGetState(i, &state) == ERROR_SUCCESS) {
                auto it = m_ControllerCommands.find(i);
                if (it != m_ControllerCommands.end()) {
                    for (auto& [button, stateMap] : it->second) {
                        bool isPressed = (state.Gamepad.wButtons & button) != 0;
                        bool wasPressed = (m_PreviousStates[i].Gamepad.wButtons & button) != 0;

                        // Only process if state changed
                        if (isPressed != wasPressed) {
                            // Handle InputState::Down
                            if (isPressed && stateMap.contains(InputState::Down)) {
                                stateMap.at(InputState::Down)->Execute();
                            }
                            // Handle InputState::Up
                            if (!isPressed && stateMap.contains(InputState::Up)) {
                                stateMap.at(InputState::Up)->Execute();
                            }
                        }

                        // For pressed state (continuous)
                        if (isPressed && stateMap.contains(InputState::Pressed)) {
                            stateMap.at(InputState::Pressed)->Execute();
                        }
                    }
                    m_PreviousStates[i] = state;
                }
            }
        }
        return true;
    }

    void XInputManager::XInputImpl::BindControllerCommand(int controllerIndex, unsigned int button, InputState state, std::unique_ptr<Command> command)
    {
        m_ControllerCommands[controllerIndex][button][state] = std::move(command);
    }

    void XInputManager::XInputImpl::ResetControllerStates()
    {
		//m_PreviousStates.clear();
    }

    XInputManager::XInputManager() : m_XInputManager(std::make_unique<XInputImpl>())
    {
    }

    XInputManager::~XInputManager() = default;

    void XInputManager::BindControllerCommand(int controllerIndex, unsigned int button, InputState state, std::unique_ptr<Command> command) const
    {
        m_XInputManager->BindControllerCommand(controllerIndex, button, state, std::move(command));
    }

    void XInputManager::ResetControllerStates()
    {
        m_XInputManager->ResetControllerStates();
    }

    bool XInputManager::ProcessInput() const
    {
        return m_XInputManager->ProcessInput();
    }

    uint16_t XInputManager::GetXInputValue(GamepadButton gamepadButton)
    {
        switch (gamepadButton)
        {
        case GamepadButton::South:
            return XINPUT_GAMEPAD_A;
        case GamepadButton::East:
            return XINPUT_GAMEPAD_B;
        case GamepadButton::West:
            return XINPUT_GAMEPAD_X;
        case GamepadButton::North:
            return XINPUT_GAMEPAD_Y;
        case GamepadButton::Back:
            return XINPUT_GAMEPAD_BACK;
        case GamepadButton::Start:
            return XINPUT_GAMEPAD_START;
        case GamepadButton::LeftStick:
            return XINPUT_GAMEPAD_LEFT_THUMB;
        case GamepadButton::RightStick:
            return XINPUT_GAMEPAD_RIGHT_THUMB;
        case GamepadButton::LeftShoulder:
            return XINPUT_GAMEPAD_LEFT_SHOULDER;
        case GamepadButton::RightShoulder:
            return XINPUT_GAMEPAD_RIGHT_SHOULDER;
        case GamepadButton::DpadUp:
            return XINPUT_GAMEPAD_DPAD_UP;
        case GamepadButton::DpadDown:
            return XINPUT_GAMEPAD_DPAD_DOWN;
        case GamepadButton::DpadLeft:
            return XINPUT_GAMEPAD_DPAD_LEFT;
        case GamepadButton::DpadRight:
            return XINPUT_GAMEPAD_DPAD_RIGHT;

        }
        return 0;
    }


}
