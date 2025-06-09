#pragma once
#include "IMovementBehaviour.h"
#include <functional>
#include <vec2.hpp>

class GridBasedMovement : public IMovementBehaviour {
public:
    using PositionConverter = std::function<glm::vec2(const glm::ivec2&)>;

    GridBasedMovement(PositionConverter converter)
        : m_converter(converter) {
    }

protected:
    PositionConverter m_converter;
    glm::ivec2 m_startGrid;
    glm::ivec2 m_targetGrid;
};