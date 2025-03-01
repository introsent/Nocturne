#pragma once
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
#include "Component.h"
#include "CacheProfiler.h"
#include "Plot.h"

namespace dae
{
    struct BenchmarkTransform
    {
        float matrix[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1 };
    };

    class GameObject3D
    {
    public:
        BenchmarkTransform transform {};
        int ID {};
    };

    class GameObject3DAlt
    {
    public:
        ~GameObject3DAlt()
        {
            delete local;
        }

        BenchmarkTransform* local = new BenchmarkTransform{};
        int ID {};
    };

    class StructVsPointerBenchmarkWindowComponent final : public Component
    {
    public:
        StructVsPointerBenchmarkWindowComponent(GameObject* owner);
        void Render() const override;
        void Update(float deltaTime) override;

    private:
        void StartStructBenchmark();
        void StartPointerBenchmark();

        std::unique_ptr<Plot> m_structPlot;
        std::unique_ptr<Plot> m_pointerPlot;
        std::unique_ptr<Plot> m_combinedPlot;

    
        bool m_isStructCalculating = false;
        bool m_isPointerCalculating = false;
        std::vector<float> m_structResults;
        std::vector<float> m_pointerResults;

   
        std::vector<float> m_lastStructResults;
        std::vector<float> m_lastPointerResults;

        std::mutex m_resultMutex;

        std::thread m_structWorkerThread;
        std::thread m_pointerWorkerThread;

        int m_sampleCount = 10;

        bool m_startStructBenchmarkRequested = false;
        bool m_startPointerBenchmarkRequested = false;
    };
}
