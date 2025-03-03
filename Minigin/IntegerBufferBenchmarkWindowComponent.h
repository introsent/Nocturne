#pragma once
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include "Component.h"
#include "CacheProfiler.h"
#include "Plot.h"

namespace dae
{
    class IntegerBufferBenchmarkWindowComponent final : public Component
    {
    public:
        IntegerBufferBenchmarkWindowComponent(GameObject* owner);
        void RenderUI() override;
        void Update(float deltaTime) override; 

    private:
        void StartBenchmark();

        std::unique_ptr<Plot> m_plot;

        bool m_isCalculating = false;
        std::vector<float> m_results;
        std::mutex m_resultMutex;
        std::thread m_workerThread;
        int m_sampleCount = 10;

        bool m_startBenchmarkRequested = false;
    };
}
