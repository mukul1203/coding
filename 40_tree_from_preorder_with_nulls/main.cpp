#include "binary_tree/binary_tree.hpp"
#include <vector>
#include <stack>
#include <optional>

using namespace tree;

template <typename T>
node_ptr<T> tree_from_pre(const std::vector<std::optional<T>> &pre)
{
    std::stack<node_ptr<T>> S;
    S.push(node_ptr<T>(new node<T>(-1, nullptr, nullptr))); // dummy node
    bool left = true;
    for (const auto &e : pre)
    {
        if (e)
        {
            auto new_node = node_ptr<T>(new node<T>(*e, nullptr, nullptr));
            if (left)
            {
                S.top()->left = new_node;
            }
            else
            {
                S.top()->right = new_node;
                left = true;
            }
            S.push(new_node);
        }
        else if (left)
        { // left child is found null, turn to right child
            left = false;
        }
        else
        { // right child is found null, climb up the tree to reach inorder successor
            auto cur = S.top();
            S.pop();
            while (!S.empty() && cur == S.top()->right)
            {
                cur = S.top();
                S.pop();
            }
        }
    }
    return S.top()->left;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("tree from preorder with markers")
{
    std::vector<std::optional<int>> pre = {1, 3, 11, std::nullopt, std::nullopt, 7, 13, std::nullopt, std::nullopt, std::nullopt, 2, 5, 12, std::nullopt, std::nullopt, std::nullopt, 4, std::nullopt, std::nullopt};
    auto root = tree_from_pre<int>(pre);
    REQUIRE(to_vector(root) == std::vector<int>{1, 3, 2, 11, 7, 5, 4, 13, 12});
}