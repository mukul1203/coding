#include <vector>
#include <set>
#include <random>

int rng(int i, int j)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return std::uniform_int_distribution<>(i, j)(gen);
}

namespace v1
{
    std::vector<int> random_permutation(int n)
    {
        std::vector<int> v;
        v.reserve(n);
        std::vector<int> s;
        s.reserve(n);
        for (int i = 0; i < n; ++i)
            s.push_back(i);
        for (int i = 0; i < n; ++i)
        {
            int r = rng(0, n - i - 1);
            v.push_back(*(s.begin() + r));
            s.erase(s.begin() + r);
        }
        return v;
    }
}

namespace v2
{
    std::vector<int> random_permutation(int n)
    {
        std::vector<int> v(n);
        std::iota(v.begin(), v.end(), 0);
        for (int i = 0; i < n; ++i)
        {
            int r = rng(i, n - 1);
            std::swap(v[i], v[r]);
        }
        return v;
    }
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("random permutation")
{
    // This test is meant to fail. We just want to print the two random vectors.
    REQUIRE(v1::random_permutation(6) == v2::random_permutation(6));
}