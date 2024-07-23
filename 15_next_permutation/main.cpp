#include <vector>

std::vector<int> &next_perm(std::vector<int> &v)
{
    for (int i = v.size() - 2; i >= 0; --i)
    {
        // i is the inversion point
        if (v[i] < v[i + 1])
        {
            // find first element > v[i] in range [v.size()-1, i+1]
            auto iter = std::upper_bound(v.rbegin(), v.rend() - i - 1, v[i]);
            // swap the upper bound with inversion point
            std::swap(v[i], *iter);
            // from inversion point onwards, the array should be made increasing order i.e reversed, to get minimum number
            std::reverse(v.rbegin(), v.rend() - i - 1);
            return v;
        }
    }
    v.clear();
    return v;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("next permutation")
{
    SECTION("first")
    {
        std::vector<int> v{3, 1, 2};
        REQUIRE(next_perm(v) == std::vector<int>{3, 2, 1});
    }
    SECTION("second")
    {
        std::vector<int> v{1, 9, 2, 8, 7, 6};
        REQUIRE(next_perm(v) == std::vector<int>{1, 9, 6, 2, 7, 8});
    }
    SECTION("third")
    {
        std::vector<int> v{1};
        REQUIRE(next_perm(v) == std::vector<int>{});
    }
    SECTION("fourth")
    {
        std::vector<int> v{1, 9, 2, 8, 7, 1};
        REQUIRE(next_perm(v) == std::vector<int>{1, 9, 7, 1, 2, 8});
    }
    SECTION("fifth")
    {
        std::vector<int> v{6, 2, 1, 5, 4, 3, 0};
        REQUIRE(next_perm(v) == std::vector<int>{6, 2, 3, 0, 1, 4, 5});
    }
}