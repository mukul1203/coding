#include "binary_tree/binary_tree.hpp"
#include <vector>
#include <deque>

template <typename T>
std::vector<T> alternating(node_ptr<T> root)
{
    if (!root)
        return {};
    std::vector<T> res;
    std::deque<std::pair<int, node_ptr<T>>> Q;
    Q.push_back({0, root});
    while (!Q.empty())
    {
        auto [d, n] = Q.front();
        // peek the front
        // if node depth is odd, pop from front
        if (d & 1)
        {
            Q.pop_front();
            if (n->left)
                Q.push_back({d + 1, n->left});
            if (n->right)
                Q.push_back({d + 1, n->right});
        }
        else
        {
            // if node depth is even, pop from back
            std::tie(d, n) = Q.back();
            Q.pop_back();
            if (n->left)
                Q.push_back({d + 1, n->left});
            if (n->right)
                Q.push_back({d + 1, n->right});
        }
        res.push_back(n->val);
    }
    return res;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("alternating level order")
{
    {
        auto root = make_binary_tree<int>({1, 2, 3, 4, 5, 6, 7}, 0);
        REQUIRE(to_vector(root) == std::vector<int>{1, 2, 3, 4, 5, 6, 7});
        REQUIRE(alternating(root) == std::vector<int>{1, 2, 3, 7, 6, 5, 4});
    }

    {
        auto root = make_binary_tree<int>({1, std::nullopt, 2, std::nullopt, std::nullopt, std::nullopt, 3}, 0);
        REQUIRE(to_vector(root) == std::vector<int>{1, 2, 3});
        REQUIRE(alternating(root) == std::vector<int>{1, 2, 3});
    }

    {
        auto root = make_binary_tree<int>({1, 2, std::nullopt, 3, std::nullopt, std::nullopt, std::nullopt}, 0);
        REQUIRE(to_vector(root) == std::vector<int>{1, 2, 3});
        REQUIRE(alternating(root) == std::vector<int>{1, 2, 3});
    }

    {
        auto root = make_binary_tree<int>({1, std::nullopt, 2, std::nullopt, std::nullopt, 3, std::nullopt}, 0);
        REQUIRE(to_vector(root) == std::vector<int>{1, 2, 3});
        REQUIRE(alternating(root) == std::vector<int>{1, 2, 3});
    }

    {
        auto root = make_binary_tree<int>({1}, 0);
        REQUIRE(to_vector(root) == std::vector<int>{1});
        REQUIRE(alternating(root) == std::vector<int>{1});
    }
}