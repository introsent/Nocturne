#include "DeadState.h"
#include "QBertPlayer.h"
#include <iostream>
#include "AnimationComponent.h"
#include "IdleState.h"
#include "Scene.h"
#include "SceneManager.h"
#include <SoundServiceLocator.h>

void DeadState::Enter(QBertPlayer*) {
    auto dialogueCloud = std::make_unique<dae::GameObject>();

    dialogueCloud->AddComponent<dae::TextureComponent>(dialogueCloud.get(), "Qbert Curses.png");
    dialogueCloud->SetParent(owner);
    dialogueCloud->SetLocalPosition(m_dialogueCloudLocalOffset);

    m_dialogueCloud = dialogueCloud.get();
    dae::SceneManager::GetInstance().GetActiveScene()->Add(std::move(dialogueCloud));

    dae::SoundServiceLocator::GetService()->PlaySound("swearing");

    owner->GetComponent<QBertPlayer>()->ReduceHealth();

    m_deathTimer = 0.f;
}

std::unique_ptr<QBertState> DeadState::Update(QBertPlayer* player, float deltaTime) {
    m_deathTimer += deltaTime;
    if (m_deathTimer >= DEATH_DURATION) {
        player->Respawn();
        return std::make_unique<IdleState>(owner);
    }
    return nullptr;
}

void DeadState::Exit(QBertPlayer*)
{
    m_dialogueCloud->MarkForDestroy();

}
