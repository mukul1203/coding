#include <vector>

namespace v1
{
    std::vector<int> boundary(const std::vector<std::vector<int>> &a, int i, int j, int m, int n)
    {
        int start_row = i, start_col = j;
        std::vector<int> res;
        while (j < n)
            res.push_back(a[i][j++]);
        --j;
        ++i;
        while (i < m)
            res.push_back(a[i++][j]);
        --i;
        --j;
        while (j >= start_col)
            res.push_back(a[i][j--]);
        ++j;
        --i;
        while (i > start_row)
            res.push_back(a[i--][j]);
        return res;
    }

    std::vector<int> spiral(const std::vector<std::vector<int>> &a)
    {
        std::vector<int> res;
        int m = a.size();
        int n = a[0].size();
        int i = 0, j = 0;
        while (i < m && j < n)
        {
            auto b = boundary(a, i++, j++, m--, n--);
            std::move(b.begin(), b.end(), std::back_inserter(res));
        }
        return res;
    }
}

namespace v2
{
    struct square_matrix
    {
        using model_t = std::vector<std::vector<int>>;

        struct iterator
        {
            int _si{0}, _sj{0}, _i{0}, _j{0}, _di{0}, _dj{0}, _m{0}, _n{0};
            const model_t &_a;
            void reset()
            {
                _si = 0;
                _sj = 0;
                _i = 0;
                _j = 0;
                _di = 0;
                _dj = 0;
                _m = 0;
                _n = 0;
            }
            iterator(const model_t &a) : _a(a)
            {
                reset();
            };
            iterator(int i, int j, int di, int dj, int m, int n, const model_t &a) : _si(i), _sj(j), _i{i}, _j{j}, _di{di}, _dj{dj}, _m(m), _n(n), _a(a) {}
            void operator++()
            {
                _i += _di;
                _j += _dj;
                if (_j >= _n)
                {
                    --_j;
                    ++_i;
                    _di = 1;
                    _dj = 0;
                }
                if (_i >= _m)
                {
                    --_i;
                    --_j;
                    _di = 0;
                    _dj = -1;
                }
                if (_j < _sj)
                {
                    ++_j;
                    --_i;
                    _dj = 0;
                    _di = -1;
                }
                if (_i < _si)
                {
                    ++_i;
                }
                if (_i == _si && _j == _sj)
                {
                    ++_i;
                    ++_j;
                    _di = 0;
                    _dj = 1;
                    _si = _i;
                    _sj = _j;
                    --_m;
                    --_n;
                    if (_i >= _m && _j >= _n)
                    {
                        reset();
                    }
                }
            }
            int operator*()
            {
                return _a[_i][_j];
            }

            static iterator end(const model_t &a)
            {
                return iterator(a);
            }

            bool operator==(const iterator &other)
            {
                return _si == other._si &&
                       _sj == other._sj &&
                       _i == other._i &&
                       _j == other._j &&
                       _di == other._di &&
                       _dj == other._dj &&
                       _m == other._m &&
                       _n == other._n;
            }

            bool operator!=(const iterator &other)
            {
                return !(*this == other);
            }
        };

        iterator begin()
        {
            return iterator(0, 0, 0, 1, a.size(), a[0].size(), a);
        }
        iterator end()
        {
            return iterator::end(a);
        }

        square_matrix(const model_t &x) : a(x) {}

    private:
        const model_t &a;
    };

    std::vector<int> spiral(const std::vector<std::vector<int>> &a)
    {
        std::vector<int> res;
        square_matrix sa(a);
        for (const auto &e : sa)
        {
            res.push_back(e);
        }
        return res;
    }
}

namespace mukul = v2;
#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("spiral matrix")
{
    REQUIRE(mukul::spiral({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}) == std::vector<int>{1, 2, 3, 6, 9, 8, 7, 4, 5});
    REQUIRE(mukul::spiral({{1}}) == std::vector<int>{1});
    REQUIRE(mukul::spiral({{1, 2}, {3, 4}}) == std::vector<int>{1, 2, 4, 3});
}