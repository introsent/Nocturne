#pragma once
#include <memory>
#include "Component.h"
#include "Level.h"
#include "CoilyState.h"
#include "PositionProxy.h"
#include "AnimationComponent.h"
#include "PositionConverters.h"

class Enemy : public dae::Component{
public:
    Enemy(dae::GameObject* owner, Level* level, const IPositionProxy& qbertPositionProxy, PositionConverter converter);
    virtual ~Enemy() = default;

    virtual void Update(float deltaTime) override;
    void MoveTo(const glm::ivec2& gridPos);
    void LookAt(const glm::ivec2& direction);

    virtual bool ShouldDamageQBert() const { return true; }

	glm::ivec2 GetCurrentLookAtDirection() const { return m_currentDirection; }

    glm::ivec2 GetQBertGridPosition() const { return m_qbertPositionProxy.GetGridPosition(); }

    glm::ivec2 GetGridPosition() const { return m_currentGridPos; }
    Level* GetLevel() const { return m_pLevel; }

    Event<dae::GameObject*> OnCollisionWithQbert;

    void UpdateAnimation(int frame);

    bool AreEnemyAndQbertClose(const glm::vec2& a, const glm::vec2& b, float epsilon = 30.f)
    {
        return glm::distance(a, b) < epsilon;
    }

protected:
    PositionConverter m_converter;
    glm::ivec2 m_currentDirection{};
    glm::ivec2 m_currentGridPos{};

    void CheckQBertCollision();
private:
    bool m_isActive = true;

    Level* m_pLevel = nullptr;
    const IPositionProxy& m_qbertPositionProxy;

    AnimationComponent* m_pAnimation = nullptr;
 };
