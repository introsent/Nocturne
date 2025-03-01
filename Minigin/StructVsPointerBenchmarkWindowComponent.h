#pragma once

#include "Component.h"
#include "GameObject.h"

namespace dae
{
	class StructVsPointerBenchmarkWindowComponent final : public Component
	{
	public:
		StructVsPointerBenchmarkWindowComponent(GameObject* owner) : Component(owner) {}

		void Render() const override;
		void Update(float deltaTime) override;

	};
}


