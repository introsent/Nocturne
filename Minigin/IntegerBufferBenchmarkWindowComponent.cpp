#include "IntegerBufferBenchmarkWindowComponent.h"

#include <mutex>
#include "imgui.h"

void dae::IntegerBufferBenchmarkWindowComponent::StartBenchmark() const
{
    isCalculating = true;

    std::vector<int> data(1 << 26, 1);
    std::vector<float> computedResults = CacheProfiler::Benchmark(
        data, [](int& value) { value *= 2; }, sampleCount
    );

    {
        std::lock_guard<std::mutex> lock(resultMutex);
        results = std::move(computedResults);
    }

    isCalculating = false;
}

void dae::IntegerBufferBenchmarkWindowComponent::Render() const
{
    ImGui::Begin("Integer Benchmark");

    ImGui::InputInt("##Samples", &sampleCount);
    if (sampleCount < 1) sampleCount = 1;

    ImGui::SameLine();
    if (ImGui::Button("-")) {
        if (sampleCount > 1)
            sampleCount--;
    }

    ImGui::SameLine();
    if (ImGui::Button("+")) {
        sampleCount++;
    }

    ImGui::SameLine();
    ImGui::Text("# Samples");

    if (ImGui::Button("Trash the Cache")) {
        m_plot->ClearData();
        if (!isCalculating) {
            workerThread = std::thread([this]() { StartBenchmark(); });
            workerThread.detach();
        }
    }

    if (isCalculating) {
        ImGui::Text("Wait for it...");
    }
    else {
        std::lock_guard<std::mutex> lock(resultMutex);
        if (!results.empty()) {
            m_plot->AddData(results);
            results.clear();
        }
        m_plot->RenderPlot();
    }
    ImGui::End();
}

