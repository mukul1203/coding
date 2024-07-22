#include "test_framework/catch_amalgamated.hpp"
#include <vector>
namespace v1
{
    std::pair<int, int> paritition(std::vector<int> &v, int pivot_index)
    {
        int i = 0, j = 0, k = 0;
        int pivot = v[pivot_index];

        // Initialize
        // Invariants: i points to the first element in == pivot section. All elements before i must be < pivot.
        // j points to the first element in > pivot section
        // k is the iterator, points to the element under consideration
        while (v[i] < pivot)
            ++i;
        j = i;
        while (v[j] == pivot)
            ++j;
        k = j + 1;

        while (k < v.size())
        {
            if (v[k] < pivot)
            {
                std::swap(v[i], v[j]);
                std::swap(v[i], v[k]);
                ++i;
                ++j;
            }
            else if (v[k] == pivot)
            {
                std::swap(v[j], v[k]);
                ++j;
            }
            ++k;
        }
        return {i, j};
    }
}
namespace mukul = v1;
// main() is in catch_amalgamated.cpp, you must only write test cases here. main() here won't work.
TEST_CASE("Partition", "[partition]")
{
    std::vector<int> v = {10, 9, 5, 7, 2, 9, 6, 11, 3, 6, 8, 9, 25, 3, 39};
    int pivot_index = 9;
    int pivot = v[pivot_index];
    auto [pivot_start, after_pivot] = mukul::paritition(v, pivot_index);
    REQUIRE(pivot_start <= after_pivot);
    for (int i = 0; i < pivot_start; ++i)
    {
        REQUIRE(v[i] < pivot);
    }
    for (int i = pivot_start; i < after_pivot; ++i)
    {
        REQUIRE(v[i] == pivot);
    }
    for (int i = after_pivot; i < v.size(); ++i)
    {
        REQUIRE(v[i] > pivot);
    }
}