#include <vector>

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

int candy_count(const std::vector<int> &ranks)
{
    // i - iterate
    // keep track of candies given to i - 1 = x
    // j - start from i + 1
    // compare j with j - 1, if decreasing, keep going, till j is greater than j - 1 or end of array
    // n = j - 1, these will get 1 + 2 + 3 ... n candies,
    // where i is getting n, but we must take max(n, x+1)
    // update i to j, and loop
    int total = 0;
    int previous_candies = 0;
    int i = 0;
    while (i < ranks.size())
    {
        int j = i + 1;
        while (j < ranks.size() && ranks[j] < ranks[j - 1])
            ++j;
        int cur_candies = (i > 0 && ranks[i] > ranks[i - 1]) ? std::max(previous_candies + 1, j - i) : j - i;
        total += cur_candies;
        int n = j - i - 1;
        total += (n * (n + 1)) / 2;
        previous_candies = (i + 1 == j) ? cur_candies : 1;
        i = j;
    }
    return total;
}

TEST_CASE("candy")
{
    std::vector<int> ranks = {3, 2, 6, 4, 3, 2, 1, 5, 6, 7, 8, 9, 10};
    REQUIRE(candy_count(ranks) == 45);

    ranks = {1, 2, 3, 4, 5};
    REQUIRE(candy_count(ranks) == 15);

    ranks = {5, 4, 3, 2, 1};
    REQUIRE(candy_count(ranks) == 15);

    ranks = {1, 2, 3, 2, 1};
    REQUIRE(candy_count(ranks) == 9);

    ranks = {1, 2, 2};
    REQUIRE(candy_count(ranks) == 4);
}