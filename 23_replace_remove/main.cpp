#include <string>
using namespace std;

// replace 'a' with 'dd', remove 'b'
void replace_remove(std::string &s)
{
    int na = 0;
    int j = 0;
    // remove b's and count a's
    for (int i = 0; i < s.size(); ++i)
    {
        na += (s[i] == 'a');
        if (s[i] != 'b')
            swap(s[j++], s[i]);
    }
    // j points to one next to the string without b's
    // resize string to contain final characters, expanding a's
    s.resize(j + na);
    --j;
    // form the final string by filling chars from the end towards the beginning
    int i = s.size() - 1;
    while (j >= 0)
    {
        if (s[j] == 'a')
        {
            s[i--] = 'd';
            s[i--] = 'd';
        }
        else if (s[j] != 'b')
        {
            swap(s[i--], s[j]);
        }
        --j;
    }
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("replace a with two ds and remove b")
{
    {
        string s{"adbac"};
        replace_remove(s);
        REQUIRE(s == "dddddc");
    }
    {
        string s{"bbbb"};
        replace_remove(s);
        REQUIRE(s == "");
    }
    {
        string s{"bbbba"};
        replace_remove(s);
        REQUIRE(s == "dd");
    }
    {
        string s{"aababb"};
        replace_remove(s);
        REQUIRE(s == "dddddd");
    }
    {
        string s{"a blue whale in the blue sea"};
        replace_remove(s);
        REQUIRE(s == "dd lue whddle in the lue sedd");
    }
}