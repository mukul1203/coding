#include <vector>
#include <functional>

void my_stable_partition(std::vector<int> &v, std::function<bool(int, int)> pred, int start, int end)
{
    int i = start;
    while (i < end && !pred(v[i], i))
        ++i;
    int j = i;
    while (j < end && pred(v[j], j))
        ++j;
    while (j < end)
    {
        if (!pred(v[j], j))
        {
            for (int k = j; k > i; --k)
                std::swap(v[k], v[k - 1]);
            ++i;
        }
        ++j;
    }
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("stable partition")
{
    {
        std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        my_stable_partition(v, [](int x, int i)
                            { return x & 1; }, 0, v.size());
        REQUIRE(v == std::vector<int>{2, 4, 6, 8, 10, 1, 3, 5, 7, 9});
    }

    {
        std::vector<int> v{2, 3};
        my_stable_partition(v, [](int x, int i)
                            { return x & 1; }, 0, v.size());
        REQUIRE(v == std::vector<int>{2, 3});
    }

    {
        std::vector<int> v{3, 2};
        my_stable_partition(v, [](int x, int i)
                            { return x & 1; }, 0, v.size());
        REQUIRE(v == std::vector<int>{2, 3});
    }

    {
        std::vector<int> v{2};
        my_stable_partition(v, [](int x, int i)
                            { return x & 1; }, 0, v.size());
        REQUIRE(v == std::vector<int>{2});
    }

    {
        std::vector<int> v{1};
        my_stable_partition(v, [](int x, int i)
                            { return x & 1; }, 0, v.size());
        REQUIRE(v == std::vector<int>{1});
    }
}

void move_selected_elements(std::vector<int> &v, const std::vector<int> &selection, int destination)
{
    const auto pred = [&](int x, int i)
    { return (std::find(selection.begin(), selection.end(), i) != selection.end()); };
    my_stable_partition(v, pred, 0, destination);
    my_stable_partition(v, [&](int x, int i)
                        { return !pred(x, i); }, destination, v.size());
}

TEST_CASE("move elements")
{
    {
        std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        move_selected_elements(v, {3, 6, 9}, 0);
        REQUIRE(v == std::vector<int>{4, 7, 10, 1, 2, 3, 5, 6, 8, 9});
    }

    {
        std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        move_selected_elements(v, {3, 6, 9}, 9);
        REQUIRE(v == std::vector<int>{1, 2, 3, 5, 6, 8, 9, 4, 7, 10});
    }

    {
        std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        move_selected_elements(v, {3, 6, 9}, 5);
        REQUIRE(v == std::vector<int>{1, 2, 3, 5, 4, 7, 10, 6, 8, 9});
    }
}