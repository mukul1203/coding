#include <iostream>
#include <cassert>
#include "../test_framework/catch_amalgamated.hpp"

using namespace std;

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

namespace mukul = v1;

TEST_CASE("Parity check", "[parity]")
{
    REQUIRE(mukul::parity(7) == 1);
    REQUIRE(mukul::parity(3) == 1);
}

// int main()
// {
//     int x = 7;
//     cout << "parity of " << x << " i.e. " << hex << x << " is " << mukul::parity(x) << endl;
//     for (int i = 0; i < 1000; ++i)
//     {
//         assert(v1::parity(i) == mukul::parity(i));
//     }
//     return 0;
// }