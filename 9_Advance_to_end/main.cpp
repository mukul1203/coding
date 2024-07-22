#include "test_framework/catch_amalgamated.hpp"
#include <vector>
#include <functional>

bool advance(const std::vector<int> &v)
{
    std::vector<bool> reachable(v.size(), false);
    reachable[0] = true;
    for (int i = 1; i < v.size(); ++i)
    {
        reachable[i] = [&]()
        {
            for (int j = i - 1; j >= 0; --j)
            {
                if (reachable[j] && i - j <= v[j])
                    return true;
            }
            return false;
        }();
    }
    return reachable[v.size() - 1];
}
TEST_CASE("Advance till end", "[advance]")
{
    REQUIRE(advance({1, 0}) == true);
    REQUIRE(advance({2, 3, 4, 1, 0, 0, 3}) == true);
    REQUIRE(advance({0}) == true);
    REQUIRE(advance({0, 1}) == false);
}