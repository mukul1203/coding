#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
struct result_t
{
    int profit{0};
    int min1{0};
    int max1{0};
    int min2{0};
    int max2{0};
    std::tuple<int, int, int, int, int> as_tuple() const
    {
        return std::make_tuple(profit, min1, max1, min2, max2);
    }
    auto operator==(const result_t &o) const
    {
        return as_tuple() == o.as_tuple();
    };
};

result_t brute_max_profit(const std::vector<int> &v)
{
    int max = 0;
    result_t res{0, 0, 0, 0, 0};
    for (int i = 0; i < v.size() - 3; ++i)
    {
        for (int j = i; j < v.size(); ++j)
        {
            for (int k = j; k < v.size(); ++k)
            {
                for (int l = k; l < v.size(); ++l)
                {
                    if (v[j] - v[i] + v[l] - v[k] > max)
                    {
                        max = v[j] - v[i] + v[l] - v[k];
                        res = {max, i, j, k, l};
                    }
                }
            }
        }
    }
    return res;
}

result_t max_profit(const std::vector<int> &v)
{
    static const auto next_min = [&](int &i) -> int
    {
        while (i + 1 < v.size() && v[i] >= v[i + 1])
            ++i;
        return i;
    };
    static const auto next_max = [&](int &i) -> int
    {
        while (i + 1 < v.size() && v[i] <= v[i + 1])
            ++i;
        return i;
    };
    static const auto delta = [&](int i, int j) -> int
    {
        return v[i] - v[j];
    };

    int i = 0;
    int min1 = next_min(i);
    int max1 = next_max(i);
    int min2 = next_min(i);
    int max2 = next_max(i);
    while (i < v.size())
    {
        int min = next_min(i);
        int max = next_max(i);
        if (min == max)
            break; // end of array
        std::vector<int> x{delta(max1, min1), delta(max2, min2), delta(max1, min2), std::min(0, delta(max2, min))};
        auto min_loss = std::min_element(x.begin(), x.end());
        if (*min_loss > (max - min))
            continue;
        int d = std::distance(x.begin(), min_loss);
        if (d == 0) // throw away min1,max1 in favor of min,max
        {
            min1 = min2;
            max1 = max2;
            min2 = min;
            max2 = max;
        }
        else if (d == 1) // throw away min2,max2 in favor of min,max
        {
            min2 = min;
            max2 = max;
        }
        else if (d == 2) // throw away max1 in favor of max2
        {
            max1 = max2;
            min2 = min;
            max2 = max;
        }
        else if (d == 3) // throw away max2 in favor of max;
        {
            max2 = max;
        }
    }
    int profit = v[max1] - v[min1] + v[max2] - v[min2];
    return {profit, min1, max1, min2, max2};
}

std::ostream &operator<<(std::ostream &os, result_t const &value)
{
    os << value.profit << " " << value.min1 << " " << value.max1 << " " << value.min2 << " " << value.max2;
    return os;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"
TEST_CASE("maximum profit", "[max_profit]")
{
    REQUIRE(max_profit({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == result_t{9, 0, 9, 9, 9});

    std::vector<int> v{12, 11, 13, 9, 12, 8, 14, 13, 15, 17};
    // INFO("Vector is " << fmt::format("{}", fmt::join(v, ", ")));
    // REQUIRE(max_profit(v) == brute_max_profit(v));

    int i = 0;
    while (i++ < 101)
    {
        std::random_shuffle(v.begin(), v.end());
        INFO("Vector is " << fmt::format("{}", fmt::join(v, ", ")));
        REQUIRE(max_profit(v) == brute_max_profit(v));
    }
}