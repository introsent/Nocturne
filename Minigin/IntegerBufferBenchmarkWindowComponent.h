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
        void Render() const override;
        void Update(float deltaTime) override; // New non-const update method

    private:
        void StartBenchmark();

        std::unique_ptr<Plot> m_plot;

        // Now these members are non-mutable because state changes occur in Update()
        bool m_isCalculating = false;
        std::vector<float> m_results;
        std::mutex m_resultMutex;
        std::thread m_workerThread;
        int m_sampleCount = 10;

        // Command flag for triggering benchmark from the UI.
        bool m_startBenchmarkRequested = false;
    };
}
