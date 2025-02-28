#pragma once
#include <chrono>
#include <vector>

class CacheProfiler {
public:
    template <typename T, typename Func>
    static std::vector<int> Benchmark(std::vector<T>& data, Func operation) {
        using namespace std::chrono;
        std::vector<int> results;

        for (int stepSize = 1; stepSize <= 1024; stepSize *= 2) {
            auto start = high_resolution_clock::now();

            for (size_t i = 0; i < data.size(); i += stepSize) {
                operation(data[i]);
            }

            auto end = high_resolution_clock::now();
            auto timeTaken = static_cast<int>(duration_cast<nanoseconds>(end - start).count());

            results.push_back(timeTaken); 
        }

        return results;  
    }
};

