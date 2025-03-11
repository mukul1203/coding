#include <set>
#include <string>
#include <vector>

struct prefix_comparable
{
    const std::string &key;
    friend bool operator<(const std::string &lhs, const prefix_comparable &rhs)
    {
        return lhs.substr(0, rhs.key.size()) < rhs.key;
    }
    friend bool operator<(const prefix_comparable &lhs, const std::string &rhs)
    {
        return lhs.key < rhs.substr(0, lhs.key.size());
    }
    friend bool operator<(const prefix_comparable &lhs, const prefix_comparable &rhs)
    {
        return lhs.key < rhs.key;
    }
};
namespace v1
{
    std::vector<std::string> autocomplete(const std::string &key, const std::set<std::string, std::less<>> &dict)
    {
        auto [begin, end] = dict.equal_range(prefix_comparable{key});
        return std::vector<std::string>(begin, end);
    }
}

namespace mukul = v1;

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"
TEST_CASE("autocomplete", "[autocomplete]")
{
    std::set<std::string, std::less<>> dict = {
        "dog", "deer", "deal"};
    REQUIRE(mukul::autocomplete("de", dict) == std::vector<std::string>{"deal", "deer"});
    REQUIRE(mukul::autocomplete("d", dict) == std::vector<std::string>{"deal", "deer", "dog"});
    REQUIRE(mukul::autocomplete("dez", dict) == std::vector<std::string>{});
}