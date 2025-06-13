#include "HighscoreLoader.h"
#include <fstream>
#include <algorithm>

std::vector<std::pair<std::string, int>> HighscoreLoader::ReadHighScores()
{
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file("highscores.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos) {
                std::string name = line.substr(0, commaPos);
                int score = std::stoi(line.substr(commaPos + 1));
                scores.emplace_back(name, score);
            }
        }
        file.close();
    }
    return scores;
}

void HighscoreLoader::SaveHighScores(const std::vector<std::pair<std::string, int>>& scores)
{
    std::ofstream file("highscores.txt");
    if (file.is_open()) {
        for (const auto& entry : scores) {
            file << entry.first << "," << entry.second << "\n";
        }
        file.close();
    }
}

void HighscoreLoader::SaveHighScore(const std::string& name, int score)
{
    auto scores = ReadHighScores();
    scores.emplace_back(name, score);
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });
    if (scores.size() > 10) scores.resize(10);
    SaveHighScores(scores);
}
