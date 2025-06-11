#pragma once
#include <glm/glm.hpp>

class IPositionProxy {
public:
    virtual ~IPositionProxy() = default;
    virtual glm::ivec2 GetGridPosition() const noexcept = 0;
    virtual glm::vec2 GetWorldPosition() const noexcept = 0;
}; 
