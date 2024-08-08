#include <vector>
#include <deque>
#include <string>
#include <optional>
using namespace std;

int strtoi(const string &s, int start, int end)
{
    int res = 0;
    for (int i = start; i < end; ++i)
    {
        res = res * 10 + (s[i] - '0');
    }
    return res;
}

vector<vector<int>> valid_ip_dots(const string &s, int start, int end, int k)
{
    int n = end - start;
    int digits = n / (k + 1);
    if (digits == 0 || digits > 3)
        return {};
    if (k == 0)
    {
        if (strtoi(s, start, end) > 255)
            return {};
        return {{-1}};
    }
    vector<vector<int>> res;
    for (int i = end - 2; i >= end - 4; --i) // run three times only, as we have only three places to put a dot and then recurse
    {
        if ((i < end - 2 && s[i + 1] == '0') || strtoi(s, i + 1, end) > 255)
            continue;
        auto v = valid_ip_dots(s, start, i + 1, k - 1);
        for (auto &x : v)
            x.push_back(i);
        move(v.begin(), v.end(), back_inserter(res));
    }
    return res;
}

vector<string> valid_ips(const string &s)
{
    vector<string> res;
    auto v = valid_ip_dots(s, 0, s.size(), 3);
    transform(v.begin(), v.end(), back_inserter(res), [&](auto &dots)
              {
        int j = 1; //index in dots, ignore 0th, which is -1
        string dotted;
        for(int i = 0; i < s.size(); ++i) {
            dotted.push_back(s[i]);
            if(dots[j] == i) {dotted.push_back('.'); ++j;
            }
        }
        return dotted; });
    return res;
}
#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("valid ips")
{
    auto ips = valid_ips("19216810");
    // std::sort(ips.begin(), ips.end());
    fmt::print("IPs are {}", ips);
}