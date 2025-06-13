#include "DiscManager.h"

void DiscManager::RegisterDisc(const glm::ivec2& gridPos, dae::GameObject* pDisc)
{
    m_DiscMap[gridPos] = pDisc;
}

dae::GameObject* DiscManager::GetDiscAt(const glm::ivec2& gridPos) const
{
    auto it = m_DiscMap.find(gridPos);
    if (it != m_DiscMap.end()) {
        return it->second;
    }
    return nullptr;
}

int DiscManager::GetRemainingDiscs()
{
	return static_cast<int>(m_DiscMap.size());
}

void DiscManager::Clear()
{
    m_DiscMap.clear();
}
