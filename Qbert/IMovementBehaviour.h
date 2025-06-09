#pragma once
#include <vec3.hpp>
#include <functional>

class IMovementBehaviour {
public:
    virtual ~IMovementBehaviour() = default;

    virtual void Start(const glm::vec3& startWorld, const glm::vec3& targetWorld) = 0;
    virtual bool Update(float deltaTime) = 0; // Returns true when complete
    virtual glm::vec3 GetCurrentPosition() const = 0;
    virtual void Reset() = 0;
};
