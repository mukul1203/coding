#include "linked_list/sll.hpp"
using namespace sll;

node_ptr<int> first_overlapping_node(node_ptr<int> head1, node_ptr<int> head2)
{
    auto iter1 = head1, iter2 = head2;
    // Terminating condition is equality of iter1 and iter2.
    // They will be equal either on the first overlapping node, or when there is no overlap, both will be null and thus equal.
    while (iter1 != iter2)
    {
        // The gap between the iters after they jump back to list starts will be exactly equal to the difference of two list lengths,
        // thenceforth, they move in tandem with that gap, thus ensuring first meeting at the overlapping node if any, and if not,
        // then together meeting the list ends i.e. nullptr
        iter1 = iter1 ? iter1->next : head2; // if end of first list, move on to start of second list
        iter2 = iter2 ? iter2->next : head1; // if end of second list, move on to start of first list
    }
    return iter1;
}

#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("first overllaping node")
{
    {
        auto head1 = make_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
        auto head2 = make_list({10});
        node_ptr<int> overlapping_node = head1;
        int count = 5;
        while (count--)
        {
            overlapping_node = overlapping_node->next;
        }
        head2->next = overlapping_node; // this is node with value 6

        REQUIRE(first_overlapping_node(head1, head2) == overlapping_node);
    }

    {
        auto head1 = make_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
        auto head2 = make_list({10});
        REQUIRE(first_overlapping_node(head1, head2) == nullptr);
    }
}