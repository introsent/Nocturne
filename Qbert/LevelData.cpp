#include "LevelData.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;

std::vector<LevelData> LevelDataLoader::LoadLevels(const std::filesystem::path& filePath) {
    std::cout << filePath.root_path() << std::endl;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open level data file");
    }

    json jsonData;
    file >> jsonData;

    std::vector<LevelData> levels;
    for (const auto& levelJson : jsonData["levels"]) {
        LevelData level;
        level.index = levelJson["index"].get<int>();
        level.color_rule = levelJson["color_rule"].get<std::string>();

        for (const auto& stageJson : levelJson["stages"]) {
            StageData stage;
            stage.stage = stageJson["stage"].get<int>();

            for (const auto& enemyJson : stageJson["enemies"]) {
                EnemySpawnData enemy;
                enemy.type = enemyJson["type"].get<std::string>();

                auto pos = enemyJson["start_position"];
                enemy.start_position = {
                    pos[0].get<int>(),
                    pos[1].get<int>()
                };

                enemy.spawn_time = enemyJson["spawn_time"].get<float>();
                stage.enemies.push_back(enemy);
            }
            level.stages.push_back(stage);
        }
        levels.push_back(level);
    }
    return levels;
}