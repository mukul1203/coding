#include "linked_list/sll.hpp"
#include <functional>

template <typename T>
node_ptr<T> partition(node_ptr<T> head, std::function<bool(const T &)> pred)
{
    node_ptr<T> h1 = nullptr, h2 = nullptr, iter = head;
    while (iter && (!h1 || !h2))
    {
        if (!h1 && pred(iter->val))
            h1 = iter;
        else if (!h2 && !pred(iter->val))
            h2 = iter;
        iter = iter->next;
    }
    // now, h1 points to first node with true predicate, and h2 to first node with false predicate
    if (!h1 || !h2)
        return head; // means there are only one type of nodes, so already paritioned
    auto t1 = h1, t2 = h2;
    while (iter)
    {
        if (pred(iter->val))
        {
            t1->next = iter;
            t1 = iter;
        }
        else
        {
            t2->next = iter;
            t2 = iter;
        }
        iter = iter->next;
    }
    // now t1 points to last node with true predicate, and t2 to last node with false predicate, and each list is stitched separately
    t1->next = h2;      // link tail of truthy list to head of falsy list
    t2->next = nullptr; // tail of falsy list should be the last node
    return h1;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("linked list partition")
{
    {
        auto head = make_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
        auto new_head = partition<int>(head, [](const int &v) -> bool
                                       { return !(v & 1); });
        REQUIRE(to_vector(new_head) == std::vector<int>{2, 4, 6, 8, 1, 3, 5, 7, 9});
    }

    {
        auto head = make_list({1});
        auto new_head = partition<int>(head, [](const int &v) -> bool
                                       { return !(v & 1); });
        REQUIRE(to_vector(new_head) == std::vector<int>{1});
    }

    {
        auto head = make_list({2});
        auto new_head = partition<int>(head, [](const int &v) -> bool
                                       { return !(v & 1); });
        REQUIRE(to_vector(new_head) == std::vector<int>{2});
    }

    {
        auto head = make_list({1, 2});
        auto new_head = partition<int>(head, [](const int &v) -> bool
                                       { return !(v & 1); });
        REQUIRE(to_vector(new_head) == std::vector<int>{2, 1});
    }

    {
        auto head = make_list({2, 4});
        auto new_head = partition<int>(head, [](const int &v) -> bool
                                       { return !(v & 1); });
        REQUIRE(to_vector(new_head) == std::vector<int>{2, 4});
    }

    {
        auto head = make_list({1, 3});
        auto new_head = partition<int>(head, [](const int &v) -> bool
                                       { return !(v & 1); });
        REQUIRE(to_vector(new_head) == std::vector<int>{1, 3});
    }
}