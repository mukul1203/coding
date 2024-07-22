#include "test_framework/catch_amalgamated.hpp"
#include <deque>
#include <vector>

namespace v1
{
    std::deque<int> increment(const std::vector<int> &v)
    {
        std::deque<int> result;
        int carry = 1;
        for (int i = v.size() - 1; i >= 0; --i)
        {
            int sum = v[i] + carry;
            if (sum >= 10)
            {
                carry = 1;
                sum -= 10;
            }
            else
                carry = 0;
            result.push_front(sum);
        }
        if (carry)
            result.push_front(1);
        return result;
    }
}
namespace mukul = v1;
// main() is in catch_amalgamated.cpp, you must only write test cases here. main() here won't work.
TEST_CASE("Increment", "[increment]")
{
    REQUIRE(mukul::increment({9, 9}) == std::deque<int>{1, 0, 0});
    REQUIRE(mukul::increment({1, 9, 9}) == std::deque<int>{2, 0, 0});
    REQUIRE(mukul::increment({0}) == std::deque<int>{1});
    REQUIRE(mukul::increment({1, 1}) == std::deque<int>{1, 2});
}