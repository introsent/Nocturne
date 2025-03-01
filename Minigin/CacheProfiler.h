#pragma once
#include <chrono>
#include <vector>


    template <typename T, typename Func>
    static std::vector<float> Benchmark(std::vector<T>& data, Func operation, int sampleCount) {
        using namespace std::chrono;
        std::vector<std::vector<float>> allResults(sampleCount);

        for (int u = 0; u < sampleCount; ++u) {
            std::vector<float> results;

            for (int stepSize = 1; stepSize <= 1024; stepSize *= 2) {
                auto start = high_resolution_clock::now();

                for (size_t i = 0; i < data.size(); i += stepSize) {
                    operation(data[i]);
                }

                auto end = high_resolution_clock::now();
                results.push_back(static_cast<float>(duration_cast<microseconds>(end - start).count()));
            }

            allResults[u] = results;
        }

        // Average results across all samples
        std::vector<float> averagedResults(allResults[0].size(), 0);
        for (size_t i = 0; i < averagedResults.size(); ++i) {
            for (int j = 0; j < sampleCount; ++j) {
                averagedResults[i] += allResults[j][i];
            }
            averagedResults[i] /= float(sampleCount);
        }

        return averagedResults;
    }

