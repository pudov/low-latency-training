#include <benchmark/benchmark.h>

#include <cstdlib>
#include <list>
#include <numeric>
#include <vector>

template <typename T>
T gen() {
    unsigned seed = 42;
    T v;
    for (auto i = 0; i < 100; ++i) {
        rand_r(&seed);
        v.push_back(i);
    }
    return v;
}

int glob = 0;

static void accv(benchmark::State& state) {
    auto v = gen<std::vector<int>>();
    // prologue

    for (auto _ : state) {
        auto n = std::accumulate(v.begin(), v.end(), 0);
        benchmark::DoNotOptimize(&n);
        glob += n;
    }

    // epilogue
}
static void accl(benchmark::State& state) {
    auto v = gen<std::list<int>>();
    // prologue

    for (auto _ : state) {
        auto n = std::accumulate(v.begin(), v.end(), 0);
        benchmark::DoNotOptimize(&n);
        glob += n;
    }

    // epilogue
}

BENCHMARK(accv)->Range(1024, 128 * 1024);
BENCHMARK(accl)->Range(1024, 128 * 1024);

BENCHMARK_MAIN();
