#include <benchmark/benchmark.h>

#include <cstdlib>
#include <numeric>
#include <vector>

// static std::vector<int> gen() {
//     unsigned seed = 42;
//     std::vector<int> v;
//     for (auto i = 0; i < 100; ++i) {
//         rand_r(&seed);
//         v.push_back(i);
//     }
//     return v;
// }
//
// int glob = 0;

// static void acc(benchmark::State& state) {
//     auto v = gen();
//     // prologue
//
//     for (auto _ : state) {
//         auto n = std::accumulate(v.begin(), v.end(), 0);
//         benchmark::DoNotOptimize(&n);
//         glob += n;
//     }
//
//     // epilogue
// }

static void pb(benchmark::State& state) {
    // prologue
    size_t sz = state.range(0);
    state.SetItemsProcessed(sz);
    state.SetBytesProcessed(sz * sizeof(int));
    state.SetLabel("WTF");
    state.counters["size"] = sz;

    for (auto _ : state) {
        std::vector<int> v;
        for (size_t i = 0; i < sz; ++i) {
            v.push_back(42);
            benchmark::DoNotOptimize(v.data());
        }
    }

    // epilogue
}
static void pb_r(benchmark::State& state) {
    // prologue
    size_t sz = state.range(0);

    for (auto _ : state) {
        std::vector<int> v;
        v.reserve(sz);
        for (size_t i = 0; i < sz; ++i) {
            v.push_back(42);
            benchmark::DoNotOptimize(v.data());
        }
    }

    // epilogue
}

// BENCHMARK(acc);
BENCHMARK(pb)->Range(1024, 128 * 1024);
BENCHMARK(pb_r)->Range(1024, 128 * 1024);
// BENCHMARK(pb_r2);

BENCHMARK_MAIN();
