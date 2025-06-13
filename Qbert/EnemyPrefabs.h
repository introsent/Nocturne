#pragma once
#include <functional>
#include <memory>
#include "GameObject.h"
#include "Level.h"
#include "QBertPlayer.h"
#include <string>
#include "PositionProxy.h"
#include "MultiQbertPositionProxy.h"

class EnemyPrefabs {
public:
    using CreateEnemyFunc = std::function<std::unique_ptr<dae::GameObject>(Level* level, const glm::ivec2& gridPos, const MultiQbertPositionProxy& qbertPositionProxy)>;

	EnemyPrefabs();
    std::unique_ptr<dae::GameObject> CreateEnemy(
        const std::string& type,
        Level* level,
        const glm::ivec2& gridPos, 
        const MultiQbertPositionProxy& qbertPositionProxy);

    static std::unique_ptr<dae::GameObject> CreateCoily(Level* level, const glm::ivec2& gridPos, const MultiQbertPositionProxy& qbertPositionProxy);
    static std::unique_ptr<dae::GameObject> CreateSlick(Level* level, const glm::ivec2& gridPos, const MultiQbertPositionProxy& qbertPositionProxy);
    static std::unique_ptr<dae::GameObject> CreateSam(Level* level, const glm::ivec2& gridPos, const MultiQbertPositionProxy& qbertPositionProxy);
    static std::unique_ptr<dae::GameObject> CreateUgg(Level* level, const glm::ivec2& gridPos, const MultiQbertPositionProxy& qbertPositionProxy);
    static std::unique_ptr<dae::GameObject> CreateWrongway(Level* level, const glm::ivec2& gridPos, const MultiQbertPositionProxy& qbertPositionProxy);

    // Helper functions
    static std::unique_ptr<dae::GameObject> CreateSlickSam(Level* level, const glm::ivec2& gridPos, const MultiQbertPositionProxy& qbertPositionProxy, bool isSlick);
    static std::unique_ptr<dae::GameObject> CreateUggWrongway(Level* level, const glm::ivec2& gridPos, const MultiQbertPositionProxy& qbertPositionProxy, bool isUgg);

private:
    static inline std::unordered_map<std::string, CreateEnemyFunc> m_Prefabs;
};