#include "../test_framework/catch_amalgamated.hpp"
#include <vector>

int deduplicate(std::vector<int> &v)
{
    if (v.empty())
        return 0;

    int i = 0, j = 0;
    // invariant: i points to the last element of unique element array
    // j serves as iterator to iterate the array
    while (j < v.size())
    {
        if (v[i] != v[j])
        {
            std::swap(v[++i], v[j]);
        }
        ++j;
    }
    return i + 1;
}

TEST_CASE("Delete duplicates from a sorted array", "[deduplicate]")
{
    SECTION("first")
    {
        std::vector<int> v{1, 1, 2, 3, 4, 5, 5, 5, 5, 5, 6, 6, 7, 8, 9, 10, 10, 10};
        int n = deduplicate(v);
        REQUIRE(std::vector<int>(v.begin(), v.begin() + n) == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    }
    SECTION("second")
    {
        std::vector<int> v{-1, 21, 99, 100, 203, 203, 3000};
        int n = deduplicate(v);
        REQUIRE(std::vector<int>(v.begin(), v.begin() + n) == std::vector<int>{-1, 21, 99, 100, 203, 3000});
    }
    SECTION("third")
    {
        std::vector<int> v{0, 0, 0, 0, 0};
        int n = deduplicate(v);
        REQUIRE(std::vector<int>(v.begin(), v.begin() + n) == std::vector<int>{0});
    }
    SECTION("fourth")
    {
        std::vector<int> v{};
        int n = deduplicate(v);
        REQUIRE(std::vector<int>(v.begin(), v.begin() + n) == std::vector<int>{});
    }
}