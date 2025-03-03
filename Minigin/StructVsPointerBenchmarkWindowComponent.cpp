#include "StructVsPointerBenchmarkWindowComponent.h"
#include "imgui.h"

namespace dae
{
    StructVsPointerBenchmarkWindowComponent::StructVsPointerBenchmarkWindowComponent(GameObject* owner)
        : Component(owner)
    {
        m_structPlot = std::make_unique<Plot>("Struct Benchmark");
        m_pointerPlot = std::make_unique<Plot>("Pointer Benchmark");
        m_combinedPlot = std::make_unique<Plot>("Combined Benchmark");
    }

    void StructVsPointerBenchmarkWindowComponent::Update(float)
    {
        if (m_startStructBenchmarkRequested && !m_isStructCalculating)
        {
            m_startStructBenchmarkRequested = false;
            m_isStructCalculating = true;
            m_structWorkerThread = std::thread([this]() { StartStructBenchmark(); });
            m_structWorkerThread.detach();
        }

        if (m_startPointerBenchmarkRequested && !m_isPointerCalculating)
        {
            m_startPointerBenchmarkRequested = false;
            m_isPointerCalculating = true;
            m_pointerWorkerThread = std::thread([this]() { StartPointerBenchmark(); });
            m_pointerWorkerThread.detach();
        }

        {
            std::lock_guard<std::mutex> lock(m_resultMutex);
           
            if (!m_structResults.empty())
            {
                m_structPlot->AddData(m_structResults);
                m_lastStructResults = m_structResults;
                m_structResults.clear();
            }
            if (!m_pointerResults.empty())
            {
                m_pointerPlot->AddData(m_pointerResults);
                m_lastPointerResults = m_pointerResults; 
                m_pointerResults.clear();
            }
        }

        if (!m_isStructCalculating && !m_isPointerCalculating &&
            !m_lastStructResults.empty() && !m_lastPointerResults.empty())
        {
            m_combinedPlot->ClearData();
            m_combinedPlot->AddData(m_lastStructResults);
            m_combinedPlot->AddData(m_lastPointerResults);
        }
    }

    void StructVsPointerBenchmarkWindowComponent::StartStructBenchmark()
    {
        std::vector<GameObject3D> data(1 << 20); 
        std::vector<float> computedResults = Benchmark(
            data, [](GameObject3D& obj) { obj.ID++; }, m_sampleCount
        );
        {
            std::lock_guard<std::mutex> lock(m_resultMutex);
            m_structResults = std::move(computedResults);
        }
        m_isStructCalculating = false;
    }

   
    void StructVsPointerBenchmarkWindowComponent::StartPointerBenchmark()
    {
        std::vector<GameObject3DAlt> data(1 << 20);
        std::vector<float> computedResults = Benchmark(
            data, [](GameObject3DAlt& obj) { obj.ID++; }, m_sampleCount
        );
        {
            std::lock_guard<std::mutex> lock(m_resultMutex);
            m_pointerResults = std::move(computedResults);
        }
        m_isPointerCalculating = false;
    }

    void StructVsPointerBenchmarkWindowComponent::Render() const
    {
        ImGui::Begin("Struct vs Pointer Benchmark");

        int sampleCount = m_sampleCount;
        if (ImGui::InputInt("##Samples", &sampleCount))
        {
            const_cast<StructVsPointerBenchmarkWindowComponent*>(this)->m_sampleCount = sampleCount;
        }
        ImGui::SameLine();
        ImGui::Text("# Samples");

        if (ImGui::Button("Thrash the cache Struct"))
        {
            const_cast<StructVsPointerBenchmarkWindowComponent*>(this)->m_structPlot->ClearData();
            const_cast<StructVsPointerBenchmarkWindowComponent*>(this)->m_combinedPlot->ClearData();
            const_cast<StructVsPointerBenchmarkWindowComponent*>(this)->m_startStructBenchmarkRequested = true;
        }
        if (m_isStructCalculating)
        {
            ImGui::Text("Wait for it...");
        }
        else
        {
            m_structPlot->RenderPlot();
        }

        if (ImGui::Button("Thrash the cache Pointer"))
        {
            const_cast<StructVsPointerBenchmarkWindowComponent*>(this)->m_pointerPlot->ClearData();
            const_cast<StructVsPointerBenchmarkWindowComponent*>(this)->m_combinedPlot->ClearData();
            const_cast<StructVsPointerBenchmarkWindowComponent*>(this)->m_startPointerBenchmarkRequested = true;
        }

        if (m_isPointerCalculating)
        {
            ImGui::Text("Wait for it...");
        }
        else
        {
            m_pointerPlot->RenderPlot();
        }

        if (!m_isStructCalculating && !m_isPointerCalculating)
        {
            m_combinedPlot->RenderPlot();
        }

        ImGui::End();
    }
}
