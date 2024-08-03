#include <vector>
#include <deque>
#include <string>
#include <optional>
#include <string_view>
using namespace std;

void put_dots(string &s, deque<int> &dots)
{
    int i = s.size() - 1;
    s.resize(s.size() + dots.size());
    int j = s.size() - 1;
    while (i != j)
    {
        s[j--] = s[i];
        if (i == dots.back())
        {
            s[j] = '.';
        }
        --i;
    }
}
using junctions_t = deque<int>;

optional<vector<junctions_t>> split(const string_view &s, int n)
{
    if (s.empty() || (n == 0 && stoi(string(s)) > 255))
        return nullopt;

    // starting from begin + 1, put a dot at each position and recursively ask for n - 1 remaining dots
    vector<junctions_t> result;
    for (auto iter = s.begin() + 1; iter != s.end(); ++iter)
    {
        auto cur_idx = iter - s.begin();
        if (auto all_junctions = split(string_view(s.data() + (iter - s.begin()), s.end() - iter), n - 1))
        {
            for (auto &j : *all_junctions)
            {
                junctions_t cur;
                cur.push_back(cur_idx);
                for (auto &idx : j)
                    cur.push_back(idx + cur_idx);
                result.push_back(std::move(cur));
            }
        }
    }
    return result;
}

vector<string> valid_ips(const string &s)
{
    vector<string> res;
    if (auto junctions = split(string_view(s.data(), s.size()), 3))
    {
        for (auto &j : *junctions)
        {
            string s;
            put_dots(s, j);
            res.emplace_back(std::move(s));
        }
    }
    return res;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("valid ips")
{
    auto ips = valid_ips("19216811");
    // std::sort(ips.begin(), ips.end());
    fmt::print("IPs are {}", ips);
}