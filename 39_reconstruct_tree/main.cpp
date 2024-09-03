#include "binary_tree/binary_tree.hpp"
#include <vector>
#include <algorithm>
#include <exception>

template <typename T>
node_ptr<T> make_binary_tree_from_pre_post_order(const std::vector<T> &pre, int i, int j, const std::vector<T> &post, int k, int l)
{
    if (i == j)
        return nullptr;
    if (j == i + 1)
        return node_ptr<T>(new node<T>(pre[i], nullptr, nullptr));
    // In preorder, first node is root, next to it is left child
    // Search the left child in post order, which is unique (given the node values are unique in the problem).
    // The left child location in post order will tell us the split point between left subtree and right subtree.
    auto start = post.begin() + k, stop = post.begin() + l;
    auto itr = std::find(start, stop, pre[i + 1]);
    if (itr == stop)
        throw std::runtime_error("Invalid pre and post orders");
    int m_post = itr - post.begin() + 1;
    int m_pre = i + 1 + m_post - k;
    return node_ptr<T>(new node<T>(pre[i], make_binary_tree_from_pre_post_order(pre, i + 1, m_pre, post, k, m_post), make_binary_tree_from_pre_post_order(pre, m_pre, j, post, m_post, l - 1)));
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("binary tree from pre and post orders")
{
    std::vector<int> pre = {1, 3, 11, 4, 8, 2, 7, 6};
    std::vector<int> post = {11, 8, 4, 3, 6, 7, 2, 1};
    REQUIRE(pre.size() == 8);
    REQUIRE(post.size() == pre.size());
    auto root = make_binary_tree_from_pre_post_order<int>(pre, 0, pre.size(), post, 0, post.size());
    REQUIRE(to_vector(root) == std::vector<int>{1, 3, 2, 11, 4, 7, 8, 6});
}