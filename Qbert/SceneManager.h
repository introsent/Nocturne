#pragma once
#include <string>

namespace SceneManager
{
	void CreateGameScene(const std::string& playerName);

	void CreateNameEntryScene();

	void CreateMenuScene();

	void CreateHighscoreScene(int playerScore);
};

