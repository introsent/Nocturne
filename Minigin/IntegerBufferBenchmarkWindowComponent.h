#pragma once
#include <mutex>

#include "Component.h"
#include "CacheProfiler.h"
#include "Plot.h"

namespace dae
{
	class IntegerBufferBenchmarkWindowComponent final : public Component
	{
	public:
		IntegerBufferBenchmarkWindowComponent(GameObject* owner) : Component(owner) { m_plot = std::make_unique<Plot>("Integer benchmark"); }


		void Render() const override;
		//void Update(float deltaTime) override;

	private:
		void StartBenchmark() const;

		std::unique_ptr<Plot> m_plot;

		mutable std::atomic<bool> isCalculating = false;
		mutable std::vector<float> results;
		mutable std::mutex resultMutex;
		mutable std::thread workerThread;
		mutable int sampleCount = 10;
	};

}

