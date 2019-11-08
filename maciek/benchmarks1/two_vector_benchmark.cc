#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

std::vector<size_t> seq(size_t size) {
    size_t ind = 0;
    auto gen = [&] { return ind++; };
    std::vector<size_t> v;
    std::generate_n(std::back_inserter(v), size, gen);
    return v;
}

std::vector<size_t> randSeq(size_t size) {
    auto v = seq(size);
    std::random_device rd;
    std::mt19937 g{rd()};
    std::shuffle(v.begin(), v.end(), g);
    return v;
}

static void sequential(benchmark::State& state) {
    // prologue
    size_t sz = state.range(0);

    auto data = seq(sz);
    auto index = seq(sz);

    for (auto _ : state) {
        for (auto i : index) {
            auto x = data[i];
            benchmark::DoNotOptimize(x);
        }
    }

    // epilogue
}
static void random(benchmark::State& state) {
    // prologue
    size_t sz = state.range(0);

    auto data = seq(sz);
    auto index = randSeq(sz);

    for (auto _ : state) {
        for (auto i : index) {
            auto x = data[i];
            benchmark::DoNotOptimize(x);
        }
    }

    // epilogue
}

BENCHMARK(sequential)->RangeMultiplier(2)->Range(1024, 1024 * 1024 * 2);
BENCHMARK(random)->RangeMultiplier(2)->Range(1024, 1024 * 1024 * 2);

BENCHMARK_MAIN();