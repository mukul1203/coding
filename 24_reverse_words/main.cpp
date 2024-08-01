#include <string>
#include <algorithm>
#include <functional>
using namespace std;

void reverse_words(string &s)
{
    static const auto is_space = [](auto &c)
    { return isspace(c); };
    reverse(s.begin(), s.end());
    auto iter = find_if_not(s.begin(), s.end(), is_space);
    while (iter != s.end())
    {
        auto word_end = find_if(iter, s.end(), is_space);
        reverse(iter, word_end);
        iter = find_if_not(word_end, s.end(), is_space);
    }
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("Reverse words")
{
    {
        string s{"My name is Mukul."};
        reverse_words(s);
        REQUIRE(s == "Mukul. is name My");
    }

    {
        string s{"Hello"};
        reverse_words(s);
        REQUIRE(s == "Hello");
    }

    {
        string s{"how dare, you call me a fool! But indeed I am one..."};
        reverse_words(s);
        REQUIRE(s == "one... am I indeed But fool! a me call you dare, how");
    }
}