#include <vector>
#include <random>
#include <algorithm>
#include <map>

double rng()
{
    std::random_device rd;
    std::default_random_engine en(rd());
    return std::uniform_real_distribution<>(0, 1)(en);
}

int non_uniform_sample(const std::vector<int> &v, std::vector<double> &p)
{
    std::partial_sum(p.begin(), p.end(), p.begin());
    double r = rng();
    return v[std::upper_bound(p.begin(), p.end(), r) - p.begin()];
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"
#include <iostream>

TEST_CASE("non uniform random sample")
{
    std::map<int, int> hist;
    for (int i = 0; i < 1000; ++i)
    {
        std::vector<double> p{0.1, 0.8, 0.1};
        ++hist[non_uniform_sample({1, 2, 3}, p)];
    }
    for (auto &[k, v] : hist)
        std::cout << k << " occured " << v << " times" << std::endl;
}