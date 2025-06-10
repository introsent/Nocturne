#pragma once
#include <functional>
#include <memory>
#include "GameObject.h"
#include "Level.h"
#include "QBertPlayer.h"
#include <string>

class EnemyPrefabs {
public:
    using CreateEnemyFunc = std::function<std::unique_ptr<dae::GameObject>(Level* level, const glm::ivec2& gridPos, QBertPlayer* qbertPlayer)>;

	EnemyPrefabs();
    std::unique_ptr<dae::GameObject> CreateEnemy(
        const std::string& type,
        Level* level,
        const glm::ivec2& gridPos, 
        QBertPlayer* qbertPlayer);

    static std::unique_ptr<dae::GameObject> CreateCoily(Level* level, const glm::ivec2& gridPos, QBertPlayer* qbertPlayer);
    //static std::shared_ptr<dae::GameObject> CreateUgg(Level* level, const glm::ivec2& gridPos);
    //static std::shared_ptr<dae::GameObject> CreateWrongway(Level* level, const glm::ivec2& gridPos);
    //static std::shared_ptr<dae::GameObject> CreateSlick(Level* level, const glm::ivec2& gridPos);
    //static std::shared_ptr<dae::GameObject> CreateSam(Level* level, const glm::ivec2& gridPos);

private:
    static inline std::unordered_map<std::string, CreateEnemyFunc> m_Prefabs;
};