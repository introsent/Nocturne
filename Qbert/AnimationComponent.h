#pragma once
#include "Component.h"
#include <glm.hpp>
#include "TextureComponent.h"

class AnimationComponent final : public dae::Component {
public:
    AnimationComponent(dae::GameObject* pOwner,
        dae::TextureComponent* texComp,
        glm::ivec2 frameSize,
        int numFrames,
        float frameDuration,
        int rows,
        int cols);

    void Update(float deltaTime) override;
    void SetFrame(int frameIndex);

    // New methods for looping and auto-advance
    void SetLoopRange(int startFrame, int endFrame);
    void SetAutoAdvance(bool enable);

private:
    dae::TextureComponent* m_pTex;
    glm::ivec2             m_frameSize;
    int                    m_numFrames;
    float                  m_frameDuration; // seconds per frame
    float                  m_accTime{};
    int                    m_currentFrame{};
    int                    m_loopStart{ 0 };
    int                    m_loopEnd{ 0 };
    bool                   m_autoAdvance{ false };

    int                    m_maxRows;
    int                    m_maxCols;
};
