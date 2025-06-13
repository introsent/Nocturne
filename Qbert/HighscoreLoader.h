#pragma once
#include <vector>
#include <string>
namespace HighscoreLoader
{
	std::vector<std::pair<std::string, int>> ReadHighScores();

	void SaveHighScores(const std::vector<std::pair<std::string, int>>& scores);

	void SaveHighScore(const std::string& name, int score);

};

