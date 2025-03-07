#include "TranslationComponent.h"

dae::TranslationComponent::TranslationComponent(GameObject* owner) : 
	dae::Component(owner)
{
}

void dae::TranslationComponent::Translate(const glm::vec3& offset) const
{
	glm::vec3 currentPos = GetOwner()->GetWorldPosition();
	GetOwner()->SetLocalPosition(currentPos + offset);
}
