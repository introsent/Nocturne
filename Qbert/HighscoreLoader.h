#pragma once
#include <vector>
#include <string>
#include "GameMode.h"
namespace HighscoreLoader
{
	std::vector<std::pair<std::string, int>> ReadHighScores(GameMode mode);

	void SaveHighScores(GameMode mode, const std::vector<std::pair<std::string, int>>& scores);

	void SaveHighScore(GameMode mode, const std::string& name, int score);

};

