#pragma once
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>


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

        //for (const auto& row : allResults) {
        //    // Loop over each value in the row and print it
        //    for (const auto& value : row) {
        //        std::cout << value << " ";
        //    }
        //    // Print a newline after each row
        //    std::cout << std::endl;
        //}
        //std::cout << std::endl;

        std::vector<float> averagedResults(allResults[0].size(), 0.0f);

        std::for_each(averagedResults.begin(), averagedResults.end(), [&, i = 0](float& result) mutable {
            auto [sum, minVal, maxVal] = std::accumulate(
                allResults.begin(), allResults.end(),
                std::make_tuple(0.0f, std::numeric_limits<float>::max(), std::numeric_limits<float>::lowest()),
                [i](const auto& acc, const std::vector<float>& vec) {
                    const float val = vec[i];
                    auto [currentSum, currentMin, currentMax] = acc;
                    return std::make_tuple(
                        currentSum + val,
                        std::min(currentMin, val),
                        std::max(currentMax, val)
                    );
                }
            );

            if (sampleCount > 2) {
                sum -= (minVal + maxVal);
                result = sum / (sampleCount - 2);
            }
            else {
                result = sum / sampleCount;
            }

            ++i; 
            });
        return averagedResults;
    }

