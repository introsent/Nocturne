#pragma once
#include <memory>
#include "Component.h"
#include "Level.h"
#include "CoilyState.h"
#include "PositionProxy.h"

class Enemy : public dae::Component{
public:
	Enemy(dae::GameObject* owner, Level* level, const IPositionProxy& qbertPositionProxy)
		: Component(owner), m_pLevel(level), m_qbertPositionProxy(qbertPositionProxy) {}
    virtual ~Enemy() = default;

    virtual void Update(float deltaTime) override;
    void MoveTo(const glm::ivec2& gridPos);
    void LookAt(const glm::ivec2& direction);

	glm::ivec2 GetCurrentLookAtDirection() const { return m_currentDirection; }

    glm::ivec2 GetQBertGridPosition() const { return m_qbertPositionProxy.GetGridPosition(); }

    glm::ivec2 GetGridPosition() const { return m_currentGridPos; }
    Level* GetLevel() const { return m_pLevel; }


protected:
    glm::ivec2 m_currentDirection{};
    glm::ivec2 m_currentGridPos{};
    
private:
    bool m_isActive = true;

    Level* m_pLevel = nullptr;
    const IPositionProxy& m_qbertPositionProxy;
 };
