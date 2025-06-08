#pragma once
#include <memory>
#include "Component.h"
#include "Level.h"
#include "CoilyState.h"

class Enemy : public dae::Component{
public:
	Enemy(dae::GameObject* owner, Level* level)
		: Component(owner), m_pLevel(level) {}
    virtual ~Enemy() = default;

    virtual void Update(float deltaTime) override;
    void MoveTo(const glm::ivec2& gridPos);
    void LookAt(const glm::ivec2& direction);

    glm::ivec2 GetGridPosition() const { return m_CurrentGridPos; }
    Level* GetLevel() const { return m_pLevel; }

protected:
    glm::ivec2 m_currentDirection{};
    glm::ivec2 m_CurrentGridPos{};
    Level* m_pLevel = nullptr;
    bool m_isActive = true;
 };
