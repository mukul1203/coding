#include <iostream>
#include <cassert>
#include "test_framework/catch_amalgamated.hpp"
#include <optional>
struct point
{
    int x{0}, y{0};
    friend bool operator==(const point &a, const point &b)
    {
        return a.x == b.x && a.y == b.y;
    }
};
struct rect
{
    point top_left{0, 0};
    point bottom_right{0, 0};
    friend bool operator==(const rect &a, const rect &b)
    {
        return a.top_left == b.top_left && a.bottom_right == b.bottom_right;
    }
};

namespace v1
{
    bool do_intersect(const rect &a, const rect &b)
    {
        if (b.bottom_right.x <= a.top_left.x || b.top_left.x >= a.bottom_right.x)
            return false;
        if (b.bottom_right.y <= a.top_left.y || b.top_left.y >= a.bottom_right.y)
            return false;
        return true;
    }
    std::optional<rect> intersection(const rect &a, const rect &b)
    {
        if (!do_intersect(a, b))
            return std::nullopt;
        int x1 = std::max(a.top_left.x, b.top_left.x);
        int x2 = std::min(a.bottom_right.x, b.bottom_right.x);
        int y1 = std::max(a.top_left.y, b.top_left.y);
        int y2 = std::min(a.bottom_right.y, b.bottom_right.y);
        return rect{{x1, y1}, {x2, y2}};
    }
}

namespace mukul = v1;
// main() is in catch_amalgamated.cpp, you must only write test cases here. main() here won't work.
TEST_CASE("Intersect", "[intersection]")
{
    REQUIRE(mukul::intersection({{0, 0}, {5, 5}}, {{3, 3}, {7, 7}}).value() == rect{{3, 3}, {5, 5}});
    REQUIRE(mukul::intersection({{0, 0}, {5, 5}}, {{6, 6}, {7, 7}}) == std::nullopt);
    REQUIRE(mukul::intersection({{0, 0}, {5, 5}}, {{3, 3}, {4, 4}}).value() == rect{{3, 3}, {4, 4}});
    REQUIRE(mukul::intersection({{0, 0}, {5, 5}}, {{-1, -1}, {7, 7}}).value() == rect{{0, 0}, {5, 5}});
    REQUIRE(mukul::intersection({{0, 0}, {5, 5}}, {{5, 5}, {7, 7}}) == std::nullopt);
}