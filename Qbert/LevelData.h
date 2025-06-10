#pragma once
#include <vector>
#include <string>
#include <glm.hpp>
#include <filesystem>
		

struct EnemySpawnData {
    std::string type;
    glm::ivec2 start_position;
    float spawn_time;
};

struct StageData {
    int stage;
    std::vector<EnemySpawnData> enemies;
};

struct LevelData {
    int index;
    std::string color_rule;
    std::vector<StageData> stages;
};

class LevelDataLoader {
public:
    static std::vector<LevelData> LoadLevels(const std::filesystem::path& filePath);
};