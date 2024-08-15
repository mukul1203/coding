#include <memory>
#include <optional>
#include <vector>
#include <queue>

template <typename T>
struct node;

template <typename T>
using node_ptr = std::shared_ptr<node<T>>;

template <typename T>
struct node
{
    T val;
    node_ptr<T> left;
    node_ptr<T> right;
    node(T x, node_ptr<T> l, node_ptr<T> r) : val(std::move(x)), left(std::move(l)), right(std::move(r)) {}
};

// i -> 2i+1, 2i+2
template <typename T>
node_ptr<T> make_binary_tree(const std::initializer_list<std::optional<T>> &l, int i)
{
    if (i >= l.size())
        return nullptr;
    auto ith = *(l.begin() + i);
    if (!ith)
        return nullptr;
    node_ptr<T> new_node = node_ptr<T>(new node<T>(*ith, make_binary_tree(l, 2 * i + 1), make_binary_tree(l, 2 * i + 2)));
    return new_node;
}

template <typename T>
std::vector<T> to_vector(node_ptr<T> root)
{
    std::vector<T> v;
    std::queue<node_ptr<T>> Q;
    Q.push(root);
    while (!Q.empty())
    {
        if (auto n = Q.front())
        {
            v.push_back(n->val);
            Q.push(n->left);
            Q.push(n->right);
        }
        Q.pop();
    }
    return v;
}