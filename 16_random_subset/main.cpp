#include <vector>
#include <unordered_map>
#include <random>

int rng(int i, int j)
{
    std::random_device rd;
    std::default_random_engine en(rd());
    return std::uniform_int_distribution<>(i, j)(en);
}

std::vector<int> random_subset(int n, int k)
{
    std::vector<int> result(k);
    std::unordered_map<int, int> m;
    static const auto at = [&](int i) -> int
    {
        return m.count(i) ? m[i] : i;
    };

    for (int i = 0; i < k; ++i)
    {
        int r = rng(i, n - 1);
        // We are at i, want to pick rth element from an imaginary A[0,n-1] array and swap it with ith element.
        // Since we don't want to store the A[0,n-1], we just store the elements in A affected by swapping so far, in hash map m.
        // Here, we first put whatever is at A[i] into result[i]. A[i] could be i itself, or may come from m[i].
        // Now, we also put m[r] = whatever is at r currently, which may be r, or m[r].
        // We do these steps so that we have two stable memory locations now for swapping the values.
        // By swap, we put rth value in result[i], and we also update the m[r] with value at i.
        result[i] = at(i);
        m[r] = at(r);
        std::swap(result[i], m[r]);
    }
    return result;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("random subset")
{
    REQUIRE(random_subset(10, 5) == std::vector<int>{});
}