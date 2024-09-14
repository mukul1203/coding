#include "binary_tree/binary_tree.hpp"
#include <vector>
#include <stack>

using namespace tree;

template <typename T>
std::vector<T> inorder(const node_ptr<T> &root)
{
    std::vector<T> result;
    if (!root)
        return result;
    std::stack<std::tuple<bool, bool, node_ptr<T>>> S;
    S.push({false, false, root});
    while (!S.empty())
    {
        auto &[left_visited, right_visited, top] = S.top();

        if (!left_visited)
        {
            left_visited = true;
            if (top->left)
            {
                S.push({false, false, top->left});
                continue;
            }
        }

        if (left_visited && !right_visited)
            result.push_back(top->val);

        if (!right_visited)
        {
            right_visited = true;
            if (top->right)
            {
                S.push({false, false, top->right});
                continue;
            }
        }
        S.pop();
    }
    return result;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("inorder iterative")
{
    auto root = make_binary_tree<int>({1, 2, 3, 4, 5, std::nullopt, std::nullopt, std::nullopt, 7, 6}, 0);
    REQUIRE(to_vector(root) == std::vector<int>{1, 2, 3, 4, 5, 7, 6});

    REQUIRE(inorder(root) == std::vector<int>{4, 7, 2, 6, 5, 1, 3});
}