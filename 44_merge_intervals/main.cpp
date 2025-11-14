#include <vector>

using Interval = std::pair<int, int>;
using Intervals = std::vector<Interval>;

Intervals merge_intervals(const Intervals &intervals)
{
    if (intervals.empty())
        return {};
    Intervals intervals_cpy = intervals;
    std::sort(intervals_cpy.begin(), intervals_cpy.end());
    // while second pointer doesn't fall off the end of intervals array, keep iterating
    // If next interval overlaps with the last merged interval, expand the merged interval
    // If next interval doesn't overlap, the last merged interval goes in result set, and the current interval becomes merged interval
    Intervals result;
    Interval merged = intervals_cpy[0];
    auto i = 1;
    while (i < intervals_cpy.size())
    {
        if (intervals_cpy[i].first <= merged.second)
        {
            merged.second = intervals_cpy[i].second;
        }
        else
        {
            result.push_back(merged);
            merged = intervals_cpy[i];
        }
        ++i;
    }
    result.push_back(merged);
    return result;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("merge intervals")
{
    Intervals intervals = {{1, 3}, {2, 4}};
    REQUIRE(merge_intervals(intervals) == Intervals({{1, 4}}));

    intervals = {{1, 3}};
    REQUIRE(merge_intervals(intervals) == Intervals({{1, 3}}));

    intervals = {};
    REQUIRE(merge_intervals(intervals) == Intervals({}));

    intervals = {{1, 3}, {200, 400}, {100, 150}, {2, 100}};
    REQUIRE(merge_intervals(intervals) == Intervals({{1, 150}, {200, 400}}));
}