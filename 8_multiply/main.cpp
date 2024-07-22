#include "test_framework/catch_amalgamated.hpp"
#include <deque>
#include <vector>

namespace v1
{
    std::deque<int> add(const std::deque<int> &a, const std::deque<int> &b)
    {
        std::deque<int> result;
        int carry = 0;
        int i = a.size() - 1, j = b.size() - 1;
        while (i >= 0 || j >= 0)
        {
            int a_digit = i < 0 ? 0 : a[i];
            int b_digit = j < 0 ? 0 : b[j];
            int sum = a_digit + b_digit + carry;
            carry = sum / 10;
            sum = sum % 10;
            result.push_front(sum);
            --i;
            --j;
        }
        if (carry)
            result.push_front(carry);
        return result;
    }

    std::deque<int> mult(const std::deque<int> &a, int x)
    {
        std::deque<int> result;
        int carry = 0;
        for (int i = a.size() - 1; i >= 0; --i)
        {
            int num = a[i] * x + carry;
            carry = num / 10;
            num = num % 10;
            result.push_front(num);
        }
        if (carry)
            result.push_front(carry);
        return result;
    }

    std::deque<int> mult(const std::deque<int> &a, const std::deque<int> &b)
    {
        std::deque<int> result;
        for (int i = b.size() - 1; i >= 0; --i)
        {
            auto row = mult(a, b[i]);
            int j = b.size() - 1 - i;
            while (j--)
            {
                row.push_back(0);
            }
            result = add(result, row);
        }
        return result;
    }
}
namespace mukul = v1;
// main() is in catch_amalgamated.cpp, you must only write test cases here. main() here won't work.
TEST_CASE("Add", "[add]")
{
    REQUIRE(mukul::add({9, 9}, {1}) == std::deque<int>{1, 0, 0});
    REQUIRE(mukul::add({1, 9, 9}, {2}) == std::deque<int>{2, 0, 1});
    REQUIRE(mukul::add({0}, {20}) == std::deque<int>{2, 0});
    REQUIRE(mukul::add({1, 1}, {99}) == std::deque<int>{1, 1, 0});
}

TEST_CASE("Multiply by a digit", "[mult]")
{
    REQUIRE(mukul::mult({1, 2}, 9) == std::deque<int>{1, 0, 8});
}

TEST_CASE("Multiply numbers", "[mult]")
{
    REQUIRE(mukul::mult({1, 2}, {1, 2}) == std::deque<int>{1, 4, 4});
    REQUIRE(mukul::mult({9, 9}, {1, 0, 0}) == std::deque<int>{9, 9, 0, 0});
    REQUIRE(mukul::mult({1, 2, 3, 4, 5}, {5, 4, 3, 2, 1}) == std::deque<int>{6, 7, 0, 5, 9, 2, 7, 4, 5});
}