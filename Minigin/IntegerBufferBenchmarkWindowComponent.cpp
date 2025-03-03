#include "IntegerBufferBenchmarkWindowComponent.h"
#include "imgui.h"

dae::IntegerBufferBenchmarkWindowComponent::IntegerBufferBenchmarkWindowComponent(GameObject* owner)
    : Component(owner)
{
    m_plot = std::make_unique<Plot>("Integer benchmark");
}

void dae::IntegerBufferBenchmarkWindowComponent::Update(float)
{
    if (m_startBenchmarkRequested && !m_isCalculating)
    {
        m_startBenchmarkRequested = false;
        m_isCalculating = true;
        m_workerThread = std::thread([this]() { StartBenchmark(); });
        m_workerThread.detach();
    }

    {
        std::lock_guard<std::mutex> lock(m_resultMutex);
        if (!m_results.empty())
        {
            m_plot->AddData(m_results);
            m_results.clear();
        }
    }
}

void dae::IntegerBufferBenchmarkWindowComponent::StartBenchmark()
{

    std::vector<int> data(1 << 26, 1);
    std::vector<float> computedResults = Benchmark(
        data, [](int& value) { value *= 2; }, m_sampleCount
    );

    {
        std::lock_guard<std::mutex> lock(m_resultMutex);
        m_results = std::move(computedResults);
    }
    m_isCalculating = false;
}

void dae::IntegerBufferBenchmarkWindowComponent::RenderUI() 
{
    ImGui::Begin("Integer Benchmark");

    int sampleCount = m_sampleCount;
    if (ImGui::InputInt("##Samples", &sampleCount))
    {
        m_sampleCount = sampleCount;
    }
    ImGui::SameLine();
    ImGui::Text("# Samples");

    if (ImGui::Button("Thrash the Cache"))
    {
        m_plot->ClearData();
        m_startBenchmarkRequested = true;
    }

    if (m_isCalculating)
    {
        ImGui::Text("Wait for it...");
    }
    else
    {
        m_plot->RenderPlot();
    }
    ImGui::End();
}
