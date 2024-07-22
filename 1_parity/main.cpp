#include <iostream>
#include <cassert>
#include "test_framework/catch_amalgamated.hpp"

using namespace std;

// Brute force
namespace v1
{
    template <typename T>
    bool parity(T val)
    {
        bool ret = false;
        while (val)
        {
            ret ^= (val & 0x1);
            val >>= 1;
        }
        return ret;
    }
}

// Optimized, only traversing the ON bits
namespace v2
{
    template <typename T>
    bool parity(T val)
    {
        bool ret = false;
        while (val)
        {
            val = val & (val - 1);
            ret = !ret;
        }
        return ret;
    }
}

// For large number of 64 bit words, how to calculate parity?
// Approach 1:
namespace v3
{

}

namespace mukul = v2;

// main() is in catch_amalgamated.cpp, you must only write test cases here. main() here won't work.
TEST_CASE("Parity check", "[parity]")
{
    REQUIRE(mukul::parity(7) == 1);
    REQUIRE(mukul::parity(3) == 0);
}