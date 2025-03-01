#include "Plot.h"

#include <numeric>
#include <string>
#include <algorithm>
#include "implot.h"

dae::Plot::Plot(std::string&& name) : m_plotName(std::move(name))
{
}

void dae::Plot::RenderPlot() const
{
	if (!m_dataY.empty())
	{
		if (ImPlot::BeginPlot(m_plotName.c_str())) {
			ImPlot::SetupAxesLimits(0, 1024, 0, m_maxY);
			ImPlotLineFlags flags = ImPlotLineFlags_None;
			int offset = 0;
			int stride = sizeof(float);
			int index = 0;
			for (const auto& line : m_dataY) {
				std::string label = "Line" + std::to_string(index);
				ImPlot::PlotLine(label.c_str(), m_dataX.data(), line.data(), int(line.size()), flags, offset, stride);
				++index;
			}

			ImPlot::EndPlot();
		}
	}
	
}

void dae::Plot::AddData(const std::vector<float>& newData)
{
	if (newData.size() != m_dataX.size())
	{
		m_dataX = [](size_t n) {
			std::vector<float> v(n);
			float value = 1.0f;
			for (size_t i = 0; i < n; ++i) {
				v[i] = value;
				value *= 2.0f;
			}
			return v;
			}(newData.size());
	}

	m_dataY.emplace_back(newData);

	float maxVal = std::numeric_limits<float>::lowest();
	for (const auto& row : m_dataY) {
		if (!row.empty()) {
			float rowMax = *std::max_element(row.begin(), row.end());
			maxVal = std::max(maxVal, rowMax);
		}
	}

	m_maxY = maxVal;
}


void dae::Plot::ClearData()
{
	m_dataX.clear();
	m_dataY.clear();
}


