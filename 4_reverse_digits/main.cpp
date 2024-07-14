#include <iostream>
#include <cassert>
#include "../test_framework/catch_amalgamated.hpp"

namespace v1
{
    int reverse(int x)
    {
        int result = 0;
        bool neg = (x < 0) && (x = -x);
        while (x)
        {
            result = result * 10 + x % 10;
            x /= 10;
        }
        return neg ? -result : result;
    }
}

namespace v2
{
    int reverse(int x)
    {
        int result = 0;
        while (x)
        {
            result = result * 10 + x % 10;
            x /= 10;
        }
        return result;
    }
}

namespace mukul = v2;
// main() is in catch_amalgamated.cpp, you must only write test cases here. main() here won't work.
TEST_CASE("Reverse digits", "[reverse]")
{
    REQUIRE(mukul::reverse(7) == 7);
    REQUIRE(mukul::reverse(11) == 11);
    REQUIRE(mukul::reverse(100) == 1);
    REQUIRE(mukul::reverse(-23) == -32);
}