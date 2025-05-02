// AnimationComponent.h
#pragma once
#include "Component.h"
#include <glm.hpp>
#include "TextureComponent.h"

class AnimationComponent final : public dae::Component {
public:
    AnimationComponent(dae::GameObject* pOwner,
                       dae::TextureComponent* texComp,
                       glm::vec2 frameSize,
                       int numFrames,
                       float frameDuration);

    void Update(float deltaTime) override;

    void SetFrame(int frameIndex);

private:
    dae::TextureComponent* m_pTex;
    glm::vec2              m_frameSize;
    int                    m_numFrames;
    float                  m_frameDuration; // seconds per frame
    float                  m_accTime{};
    int                    m_currentFrame{};
};

