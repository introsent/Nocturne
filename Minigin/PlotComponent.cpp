#include "PlotComponent.h"

#include <numeric>
#include <string>

#include "implot.h"

dae::PlotComponent::PlotComponent(GameObject* owner) : Component(owner)
{
}

void dae::PlotComponent::Render() const
{
	if (ImPlot::BeginPlot("Plot")) {

		ImPlotLineFlags flags = ImPlotLineFlags_None;
		int offset = 0;
		int stride = sizeof(int);  // Standard stride
		int index = 0;
		for (const auto& line : m_dataY) {
			std::string label = "Line" + std::to_string(index);
			ImPlot::PlotLine(label.c_str(), m_dataX.data(), line.data(), int(line.size()), flags, offset, stride);
			++index;
		}

		ImPlot::EndPlot();
	}
}

void dae::PlotComponent::AddYData(const std::vector<int>& newData)
{
	m_dataX = [](int n) {
		std::vector<int> v(n);
		std::iota(v.begin(), v.end(), 1);
		return v;
		}(static_cast<int>(newData.size()));

	m_dataY.emplace_back(newData);
}


