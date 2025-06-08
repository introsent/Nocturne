#pragma once
#include <memory>
#include "Component.h"
class Enemy : public dae::Component{
public:
	Enemy(dae::GameObject* owner, Level* level)
		: Component(owner), m_pLevel(level) {}
    virtual ~Enemy() = default;

    virtual void Update(float /*deltaTime*/) override {};

protected:
    glm::ivec2 m_currentDirection{};
    glm::ivec2 m_CurrentGridPos{};
    Level* m_pLevel = nullptr;
    bool m_isActive = true;
 };
