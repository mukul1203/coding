#include <iostream>
#include <cassert>
#include "../test_framework/catch_amalgamated.hpp"

namespace v1
{
    double pow(double x, unsigned int y)
    {
        double result = 1;
        while (y)
        {
            if (y & 1)
                result *= x;
            x *= x;
            y /= 2;
        }
        return result;
    }
}

namespace mukul = v1;
// main() is in catch_amalgamated.cpp, you must only write test cases here. main() here won't work.
TEST_CASE("Power", "[pow]")
{
    REQUIRE(mukul::pow(7, 2) == 49);
    REQUIRE(mukul::pow(2, 11) == 2048);
    REQUIRE(mukul::pow(11, 1) == 11);
    REQUIRE(mukul::pow(100, 3) == 1000000);
    REQUIRE(mukul::pow(2, 0) == 1);
}