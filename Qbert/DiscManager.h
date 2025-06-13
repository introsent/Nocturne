#pragma once
#include <unordered_map>
#include <memory>
#include "utils.h"
#include <Scene.h>

class DiscManager final
{
public:
    static DiscManager& GetInstance() {
        static DiscManager instance;
        return instance;
    }

    void RegisterDisc(const glm::ivec2& gridPos, dae::GameObject* pDisc);

    dae::GameObject* GetDiscAt(const glm::ivec2& gridPos) const;

    int GetRemainingDiscs();

    void Clear();

private:
    DiscManager() = default;
    ~DiscManager() = default;

    DiscManager(const DiscManager&) = delete;
    DiscManager& operator=(const DiscManager&) = delete;

    std::unordered_map<glm::ivec2, dae::GameObject*, IVec2Hash, IVec2Equal> m_DiscMap;
};

