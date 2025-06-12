#pragma once
#include "IMovementBehaviour.h"
#include "PositionConverters.h"
#include <functional>
#include <vec2.hpp>

class GridBasedMovement : public IMovementBehaviour {
public:
    GridBasedMovement(PositionConverter converter)
        : m_converter(converter) {
    }

protected:
    PositionConverter m_converter;
    glm::ivec2 m_startGrid{};
    glm::ivec2 m_targetGrid{};
};