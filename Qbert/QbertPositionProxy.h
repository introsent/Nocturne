#pragma once
#include "PositionProxy.h"
#include "QBertPlayer.h"

class QbertPositionProxy : public IPositionProxy {
public:
    explicit QbertPositionProxy(QBertPlayer* qbertPlayer);

    glm::ivec2 GetGridPosition() const noexcept override;

    glm::vec2 GetWorldPosition() const noexcept override;

    void UpdatePosition(const glm::ivec2& newPosition);

private:
    QBertPlayer* m_pQBertPlayer;
    glm::ivec2 m_gridPosition;
};