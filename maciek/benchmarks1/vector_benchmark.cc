#include <benchmark/benchmark.h>

#include <cstdlib>
#include <numeric>
#include <vector>

static std::vector<int> gen() {
    unsigned seed = 42;
    std::vector<int> v;
    for (auto i = 0; i < 100; ++i) {
        rand_r(&seed);
        v.push_back(i);
    }
    return v;
}

int glob = 0;

static void acc(benchmark::State& state) {
    auto v = gen();
    // prologue

    for (auto _ : state) {
        auto n = std::accumulate(v.begin(), v.end(), 0);
        benchmark::DoNotOptimize(&n);
        glob += n;
    }

    // epilogue
}

BENCHMARK(acc);

BENCHMARK_MAIN();
