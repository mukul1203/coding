#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>
using namespace std;

vector<vector<int>> pascal_triangle(int n)
{
    vector<vector<int>> res(n);
    res[0].push_back({1});
    for (int i = 1; i < n; ++i)
    {
        copy(res[i - 1].begin(), res[i - 1].end(), std::back_inserter(res[i]));
        res[i].push_back(0);
        adjacent_difference(res[i].begin(), res[i].end(), res[i].begin(), plus<>());
    }
    return res;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("pascal triangle")
{
    REQUIRE(pascal_triangle(1) == vector<vector<int>>{{1}});
    REQUIRE(pascal_triangle(2) == vector<vector<int>>{{1}, {1, 1}});
    REQUIRE(pascal_triangle(3) == vector<vector<int>>{{1}, {1, 1}, {1, 2, 1}});
    REQUIRE(pascal_triangle(4) == vector<vector<int>>{{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}});
    REQUIRE(pascal_triangle(5) == vector<vector<int>>{{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}});
}