#pragma once
#include "QBertState.h"
#include "TextureComponent.h"

class DeadState : public QBertState {
public:
	explicit DeadState(dae::GameObject* owner)
		: QBertState(owner) {}
    void Enter(QBertPlayer*) override;

    std::unique_ptr<QBertState> Update(QBertPlayer* player, float deltaTime) override;

    std::unique_ptr<QBertState>  HandleInput(QBertPlayer*, const glm::ivec2&) override { return nullptr; }

    void Exit(QBertPlayer*) override;

    bool CanAcceptInput() const override { return false; }

    std::string GetName() const override { return "Dead"; }

    static constexpr float DEATH_DURATION = 2.f;
private:
    std::shared_ptr<dae::GameObject> m_dialogueCloud;
	const glm::vec3 m_dialogueCloudLocalOffset{ 10.f, -32.f, 0.f };

    float m_deathTimer{ 0.f };
};


