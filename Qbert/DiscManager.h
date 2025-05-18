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

    void RegisterDisc(const glm::ivec2& gridPos, std::shared_ptr<dae::GameObject> pDisc) {
        m_DiscMap[gridPos] = std::move(pDisc);
    }

    std::shared_ptr<dae::GameObject> GetDiscAt(const glm::ivec2& gridPos) const {
        auto it = m_DiscMap.find(gridPos);
        if (it != m_DiscMap.end()) {
            return it->second;
        }
        return nullptr;
    }

    void Clear() {
        m_DiscMap.clear();
    }

private:
    DiscManager() = default;
    ~DiscManager() = default;

    DiscManager(const DiscManager&) = delete;
    DiscManager& operator=(const DiscManager&) = delete;

    std::unordered_map<glm::ivec2, std::shared_ptr<dae::GameObject>, IVec2Hash, IVec2Equal> m_DiscMap;
};

