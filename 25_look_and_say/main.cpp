#include <string>
#include <algorithm>

std::string look_n_say(int n)
{
    std::string cur = "1";
    while (--n)
    {
        std::string next;
        auto iter = cur.begin();
        do
        {
            auto mismatch = std::find_if_not(iter, cur.end(), [&](const auto &x)
                                             { return x == *iter; });
            next += std::to_string(mismatch - iter) + *iter;
            iter = mismatch;
        } while (iter != cur.end());
        cur = next;
    }
    return cur;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("look and say")
{
    REQUIRE(look_n_say(1) == "1");
    REQUIRE(look_n_say(2) == "11");
    REQUIRE(look_n_say(3) == "21");
    REQUIRE(look_n_say(4) == "1211");
    REQUIRE(look_n_say(5) == "111221");
    REQUIRE(look_n_say(6) == "312211");
    REQUIRE(look_n_say(7) == "13112221");
}