#pragma once
#include <string>
#include <vector>
#include "GameMode.h"

namespace SceneManager
{
	void CreateGameScene(GameMode mode, const std::vector<std::string>& playerNames);

	void CreateNameEntryScene(GameMode mode);

	void CreateMenuScene();

	void CreateHighscoreScene(int playerScore, GameMode mode);
};

