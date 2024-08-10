#include "linked_list/dll.hpp"

// assumes node to be that of doubly linked list, with next and prev
template <typename T>
node_ptr<T> merge(node_ptr<T> &head1, node_ptr<T> &head2)
{
    node_ptr<T> dummy_head(new node<T>());
    node_ptr<T> tail = dummy_head;
    while (head1 && head2)
    {
        if (head1->val < head2->val)
        {
            tail->next = head1;
            head1->prev = tail;
            head1 = head1->next;
        }
        else
        {
            tail->next = head2;
            head2->prev = tail;
            head2 = head2->next;
        }
        tail = tail->next;
    }
    tail->next = head1 ? head1 : head2;
    tail->next->prev = tail;
    if (dummy_head->next)
        dummy_head->next->prev = nullptr; // release the pointer to dummy_head
    return dummy_head->next;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("merge dll")
{
    auto head1 = make_list({1, 3, 5, 7, 9});
    auto head2 = make_list({2, 4, 6, 8, 10});
    auto head = merge(head1, head2);
    REQUIRE(to_vector(head) == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    auto tail = head;
    while (tail && tail->next)
        tail = tail->next;
    REQUIRE(to_vector_backwards(tail) == std::vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
}