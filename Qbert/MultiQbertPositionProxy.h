#pragma once
#include "PositionProxy.h"
#include <vector>
#include <memory>
class MultiQbertPositionProxy : public IPositionProxy {
public:
    void AddProxy(std::shared_ptr<IPositionProxy> proxy) {
        m_proxies.push_back(proxy);
    }

    glm::ivec2 GetGridPosition() const noexcept override {
        return !m_proxies.empty() ? m_proxies[0]->GetGridPosition() : glm::ivec2{ 0,0 };
    }

    glm::vec2 GetWorldPosition() const noexcept override  {
        return !m_proxies.empty() ? m_proxies[0]->GetWorldPosition() : glm::vec2{ 0,0 };
    }

    const std::vector<std::shared_ptr<IPositionProxy>>& GetAllProxies() const {
        return m_proxies;
    }

private:
    std::vector<std::shared_ptr<IPositionProxy>> m_proxies;
};