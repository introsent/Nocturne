#pragma once
#include "Component.h"

namespace dae
{
	class PlotComponent final : public Component
	{
	public:
		PlotComponent(GameObject* owner);

		void Render() const override;

		void AddYData(const std::vector<int>& newData);


	private:
		bool m_toRender{ false };

		std::vector<int> m_dataX;
		std::vector<std::vector<int>> m_dataY;
	

	};
}

