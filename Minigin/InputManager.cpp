#include <SDL.h>
#include "InputManager.h"

#include "backends/imgui_impl_sdl2.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void dae::InputManager::BindCommand(SDL_Keycode key, InputState state, Command* command)
{
}

void dae::InputManager::BindCommand(int controllerButton, InputState state, Command* command)
{
}
