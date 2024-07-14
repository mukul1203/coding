#include <iostream>
#include <cassert>
#include "../test_framework/catch_amalgamated.hpp"

namespace v1
{
    unsigned int add(unsigned int x, unsigned int y)
    {
        short carry = 0, place = 0;
        unsigned int result = 0, bit = 0;
        while (x || y)
        {
            bit = ((x & 1) xor (y & 1) xor carry) << place++;
            carry = (x & 1) & (y & 1); // Wrong!
            result |= bit;
            x >>= 1;
            y >>= 1;
        }
        return result | (carry << place);
    }
}

namespace v2
{
    unsigned int add(unsigned int x, unsigned int y)
    {
        while (y)
        {
            unsigned int carry = x & y; // x & y represents all the carries, i.e. for 111 + 101, carries will be 101.
            x = x xor y;                // bits resulting from adding each pair of bits vertically
            y = carry << 1;             // left shift carries to add them in next iteration.
        }
        return x;
    }
}

namespace mukul = v2;
// main() is in catch_amalgamated.cpp, you must only write test cases here. main() here won't work.
TEST_CASE("Add two numbers", "[add]")
{
    REQUIRE(mukul::add(7, 4) == 11);
    REQUIRE(mukul::add(3, 9) == 12);
}