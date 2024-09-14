#include "linked_list/sll.hpp"
using namespace sll;

// reverse a linked list starting from head and uptil n nodes, inclusive of head
node_ptr<int> reverse(node_ptr<int> head, int n)
{
    node_ptr<int> tail = head, cur = head, prev = nullptr, next = head->next;
    while (n--)
    {
        cur->next = prev;
        prev = cur;
        cur = next;
        next = next->next;
    }
    tail->next = cur;
    return prev;
}

void reverse_sublist(node_ptr<int> head, int s, int f)
{
    int count = s - 2;
    while (count-- > 0)
    {
        head = head->next;
    }
    head->next = reverse(head->next, f - s + 1);
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("reverse sublist")
{
    auto head = make_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
    reverse_sublist(head, 3, 7);
    REQUIRE(to_vector(head) == std::vector<int>{1, 2, 7, 6, 5, 4, 3, 8, 9});
}