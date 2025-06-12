#pragma once
#include <functional>
#include <vec2.hpp>

using PositionConverter = std::function<glm::vec2(const glm::ivec2&)>;
