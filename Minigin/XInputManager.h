#pragma once
#include <memory>

#include "Command.h"
#include "GamepadButton.h"
#include "InputState.h"

namespace dae
{
	class XInputManager final
	{
	public:
		XInputManager();
		~XInputManager();
		XInputManager(const XInputManager& other) = delete;
		XInputManager(XInputManager&& other) = delete;
		XInputManager& operator=(const XInputManager& other) = delete;
		XInputManager& operator=(XInputManager&& other) = delete;

		static uint16_t GetXInputValue(GamepadButton gamepadButton);
		bool ProcessInput() const;
		void BindControllerCommand(unsigned int button, InputState state, dae::Command* command) const;
	private:
		class XInputImpl;
		std::unique_ptr<XInputImpl> m_XInputManager;
	};
}


