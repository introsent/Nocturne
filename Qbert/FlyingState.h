#pragma once
#include "QBertState.h"

class FlyingState : public QBertState
{
public:
    explicit FlyingState(dae::GameObject* owner);
    
    void Enter(QBertPlayer* player) override;
    std::unique_ptr<QBertState> Update(QBertPlayer* player, float deltaTime) override;
    
    // Input handling remains unchanged
    std::unique_ptr<QBertState> HandleInput(QBertPlayer*, const glm::ivec2&) override { return nullptr; }
    void Exit(QBertPlayer*) override {}
    bool CanAcceptInput() const override { return false; }
    std::string GetName() const override { return "Flying"; }

private:
    enum class FlyingPhase { Flying, Dropping, Complete };

    void InitializeFlight(QBertPlayer* player);
    void UpdateFlyingPhase(float deltaTime);
    void UpdateDroppingPhase(float deltaTime);
    std::unique_ptr<QBertState> CompleteFlight(QBertPlayer* player);

    const glm::vec3 CalculateTopPosition() const;
    const glm::vec3 CalculateElevatedPosition() const;

    // Phase management
    FlyingPhase m_currentPhase{FlyingPhase::Flying};

    float m_phaseTimer{};
    const float m_flightDuration{2.f};
    const float m_dropDuration{0.5f};

    // Position data
    glm::vec3 m_qbertStartPos{};
    glm::vec3 m_discStartPos{};
    glm::vec3 m_targetWorldPos{};   
    glm::vec3 m_landingWorldPos{};   

    const glm::vec3 m_qbertLocalOffset{ 0.f, -24.f, 0.f };
    dae::GameObject* m_pDisc{nullptr};
};