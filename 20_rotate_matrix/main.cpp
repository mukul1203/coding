#include <vector>
using namespace std;

void rotate_border(vector<vector<int>> &v, int i, int j, int n)
{
    static const auto get_next = [&](pair<int, int> &p) -> pair<int, int>
    {
        return {v.size() - 1 - p.second, p.first};
    };
    while (j < n - 1)
    {
        pair<int, int> start = {i, j};
        pair<int, int> cur = start;
        pair<int, int> next = get_next(start);
        while (next != start)
        {
            swap(v[cur.first][cur.second], v[next.first][next.second]);
            cur = next;
            next = get_next(next);
        }
        ++j;
    }
}

void rotate(vector<vector<int>> &v)
{
    int i = 0, j = 0, n = v.size();
    while (i < n)
    {
        rotate_border(v, i, j, n);
        ++i;
        ++j;
        --n;
    }
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("rotate matrix")
{
    {
        vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        auto rotated = matrix;
        rotate(rotated);
        REQUIRE(rotated == vector<vector<int>>{{7, 4, 1}, {8, 5, 2}, {9, 6, 3}});
    }

    {
        vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
        auto rotated = matrix;
        rotate(rotated);
        REQUIRE(rotated == vector<vector<int>>{{13, 9, 5, 1}, {14, 10, 6, 2}, {15, 11, 7, 3}, {16, 12, 8, 4}});
    }

    {
        vector<vector<int>> matrix = {{1, 2}, {3, 4}};
        auto rotated = matrix;
        rotate(rotated);
        REQUIRE(rotated == vector<vector<int>>{{3, 1}, {4, 2}});
    }
}