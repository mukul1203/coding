#include <vector>
#include <cmath>
namespace v1
{
    bool is_prime(int i, const std::vector<int> &primes)
    {
        int root = std::pow(double(i), 0.5);
        for (const auto &p : primes)
        {
            if (p > root)
                return true;
            if (i % p == 0)
                return false;
        }
        return true;
    }
    std::vector<int> primes(int n)
    {
        std::vector<int> result;
        for (int i = 2; i <= n; ++i)
            if (is_prime(i, result))
                result.push_back(i);
        return result;
    }
}

namespace v2
{
    std::vector<int> primes(int n)
    {
        std::vector<bool> v(n + 1, true);
        std::vector<int> result;
        v[0] = v[1] = false;
        for (int i = 2; i < v.size(); ++i)
        {
            if (v[i])
            {
                for (int j = 2 * i; j < v.size(); j += i)
                    v[j] = false;
                result.push_back(i);
            }
        }
        return result;
    }
}
namespace mukul = v2;
#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"
TEST_CASE("primes to n", "[primes]")
{
    REQUIRE(mukul::primes(2) == std::vector<int>{2});
    REQUIRE(mukul::primes(3) == std::vector<int>{2, 3});
    REQUIRE(mukul::primes(27) == std::vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 23});
    REQUIRE(v1::primes(32498724) == v2::primes(32498724));
}