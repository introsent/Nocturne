#pragma once
#include <windows.h>
#include <unordered_map>
#include <vector>
#include <Xinput.h>
#include "Command.h"
#include "InputState.h"

namespace dae
{

	class XInputImpl
    {
    public:
        XInputImpl();
        ~XInputImpl() = default;

        bool ProcessInput();
        void BindControllerCommand(unsigned int button, InputState state, Command* command);

    private:
        std::unordered_map<unsigned int, std::vector<std::pair<InputState, Command*>>> m_ControllerCommands;
        XINPUT_STATE m_PreviousState{};
    };
}
