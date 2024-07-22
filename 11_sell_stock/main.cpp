#include "test_framework/catch_amalgamated.hpp"
#include <vector>

std::tuple<int, int, int> max_profit(const std::vector<int> &v)
{
    int i = 0;                                        // min price so far
    int j = 1;                                        // iterator, selling price
    int max_profit = std::numeric_limits<int>::min(); // max profit so far
    int max_i = 0, max_j = 1;
    while (j < v.size())
    {
        if (v[j] - v[i] > max_profit)
        {
            max_profit = v[j] - v[i];
            max_i = i;
            max_j = j;
        }
        if (v[j] < v[i])
            i = j;
        ++j;
    }
    return {max_profit, max_i, max_j};
}

TEST_CASE("Max profit by stock sell", "[max_profit]")
{
    REQUIRE(max_profit({310, 315, 275, 295, 260, 270, 290, 230, 255, 250}) == std::tuple<int, int, int>{30, 4, 6});
    REQUIRE(max_profit({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == std::tuple<int, int, int>{-1, 0, 1});
    REQUIRE(max_profit({10, 9, 8, 7, 6, 5, 4, 3, 2, 3}) == std::tuple<int, int, int>{1, 8, 9});
}