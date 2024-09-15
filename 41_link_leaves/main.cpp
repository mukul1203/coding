#include "binary_tree/binary_tree.hpp"
#include "linked_list/sll.hpp"

template <typename T>
void preorder(const tree::node_ptr<T> &root, sll::node_ptr<T> &tail)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        tail->next = sll::node_ptr<T>(new sll::node<T>(root->val));
        tail = tail->next;
        return;
    }
    preorder(root->left, tail);
    preorder(root->right, tail);
}

template <typename T>
sll::node_ptr<T> leaves(const tree::node_ptr<T> &root)
{
    auto dummy = sll::node_ptr<T>(new sll::node<T>());
    auto tail = dummy;
    preorder(root, tail);
    return dummy->next;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("linked list from leaves of binary tree")
{
    auto root = tree::make_binary_tree<int>({1, 2, 3, 4, 5, std::nullopt, std::nullopt, std::nullopt, 7, 6}, 0);
    REQUIRE(tree::to_vector(root) == std::vector<int>{1, 2, 3, 4, 5, 7, 6});
    REQUIRE(sll::to_vector(leaves(root)) == std::vector<int>{7, 6, 3});
}