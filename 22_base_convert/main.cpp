#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

string itos_base(long long x, int b)
{
    static const auto number_to_char = [](int n)
    {
        return n < 10 ? '0' + n : 'A' + (n - 10);
    };
    string s;
    do
    {
        s += number_to_char(x % b);
        x /= b;
    } while (x);
    reverse(s.begin(), s.end());
    return s;
}

long long stoi_base(const string &s, int b)
{
    static const auto char_to_number = [](char c)
    {
        return c < 'A' ? c - '0' : c - 'A' + 10;
    };
    long long result = 0;
    for (const auto &c : s)
    {
        result = result * b + char_to_number(c);
    }
    return result;
}

string base_convert(const string &s, int b1, int b2)
{
    return itos_base(stoi_base(s, b1), b2);
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("base convert")
{
    REQUIRE(stoi_base("10", 2) == 2);
    REQUIRE(itos_base(2, 10) == "2");
    REQUIRE(base_convert("10", 2, 10) == "2");
    REQUIRE(base_convert("10", 10, 2) == "1010");
    REQUIRE(base_convert("15", 10, 16) == "F");
    REQUIRE(base_convert("0", 2, 10) == "0");
}