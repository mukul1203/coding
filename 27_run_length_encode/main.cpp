#include <string>
#include <algorithm>

std::string encode(const std::string &s)
{
    std::string result;
    auto start = s.begin();
    while (start != s.end())
    {
        auto next = std::find_if(start, s.end(), [&](auto &x)
                                 { return x != *start; });
        result += std::to_string(next - start) + *start;
        start = next;
    }
    return result;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("run length encoding")
{
    REQUIRE(encode("a") == "1a");
    REQUIRE(encode("aa") == "2a");
    REQUIRE(encode("aaabbbb") == "3a4b");
    REQUIRE(encode("") == "");
    REQUIRE(encode("aba") == "1a1b1a");
}