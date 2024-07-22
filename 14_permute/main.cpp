#include <vector>

template <typename T>
std::vector<T> brute_permute(const std::vector<T> &v, const std::vector<int> &p)
{
    std::vector<T> result;
    result.resize(v.size());
    for (int i = 0; i < p.size(); ++i)
    {
        result[p[i]] = v[i];
    }
    return result;
}

template <typename T>
std::vector<T> &permute(std::vector<T> &v, std::vector<int> &p)
{
    int i = 0;
    while (i < p.size())
    {
        if (p[i] == -1)
        {
            ++i;
            continue;
        }
        T temp = v[i];
        int j = i;
        do
        {
            std::swap(temp, v[p[j]]);
            int k = j;
            j = p[j];
            p[k] = -1;
        } while (j != i);
        ++i;
    }
    return v;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("permute")
{
    std::vector<char> v{'a', 'b', 'c', 'd', 'e', 'f'};
    std::vector<int> p{1, 3, 5, 2, 0, 4};
    auto x = brute_permute(v, p);
    REQUIRE(x == permute(v, p));
    REQUIRE(v == std::vector<char>{'e', 'a', 'd', 'b', 'f', 'c'});
}