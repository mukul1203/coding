#include "binary_tree/binary_tree.hpp"
template <typename T>
std::pair<bool, bool> lca(node_ptr<T> root, const node_ptr<T> &x, const node_ptr<T> &y, node_ptr<T> &ans)
{
    if (!root)
        return {false, false};
    auto [bxl, byl] = lca(root->left, x, y, ans);
    if (ans)
        return {true, true};
    auto [bxr, byr] = lca(root->right, x, y, ans);
    if (ans)
        return {true, true};
    bool x_found = bxl || bxr || root == x;
    bool y_found = byl || byr || root == y;
    if (x_found && y_found)
        ans = root;
    return {x_found, y_found};
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("lca")
{
    auto root = make_binary_tree<int>({1, 2, 3, 4, 5, std::nullopt, std::nullopt, std::nullopt, 7, 6}, 0);
    REQUIRE(to_vector(root) == std::vector<int>{1, 2, 3, 4, 5, 7, 6});
    auto six = find(root, 6);
    auto seven = find(root, 7);
    auto two = find(root, 2);
    REQUIRE(six);
    REQUIRE(seven);
    node_ptr<int> ans;
    REQUIRE(lca(root, six.value(), seven.value(), ans) == std::pair<bool, bool>{true, true});
    REQUIRE(ans->val == two.value()->val);

    REQUIRE(lca(root, two.value(), seven.value(), ans) == std::pair<bool, bool>{true, true});
    REQUIRE(ans->val == two.value()->val);
}
