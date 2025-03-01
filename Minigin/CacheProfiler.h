#pragma once
#include <chrono>
#include <iostream>
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

        //for (const auto& row : allResults) {
        //    // Loop over each value in the row and print it
        //    for (const auto& value : row) {
        //        std::cout << value << " ";
        //    }
        //    // Print a newline after each row
        //    std::cout << std::endl;
        //}
        //std::cout << std::endl;

        std::vector<float> averagedResults(allResults[0].size(), 0);
        for (size_t i = 0; i < averagedResults.size(); ++i) {
            float sum = 0.0f;
            float minVal = std::numeric_limits<float>::max();
            float maxVal = std::numeric_limits<float>::lowest();

            for (int j = 0; j < sampleCount; ++j) {
                float value = allResults[j][i];
                sum += value;
                if (value < minVal)
                    minVal = value;
                if (value > maxVal)
                    maxVal = value;
            }

            if (sampleCount > 2) {
                sum -= (minVal + maxVal);
                averagedResults[i] = sum / float(sampleCount - 2);
            }
            else {
                averagedResults[i] = sum / float(sampleCount);
            }
        }

        return averagedResults;
    }

