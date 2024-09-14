#pragma once

// REVIST: Using this header only for my own code to be included in multiple places
// without including any other headers, because the including file includes this
// within a namespace, and I want only my code to be within that namespace, not any
// other headers. Users of this header file must include memory and vector headers to get
// things working.
// #include <memory>
// #include <vector>

template <typename T>
struct node;

template <typename T>
using node_ptr = std::shared_ptr<node<T>>;

template <typename T>
std::vector<T> to_vector(node_ptr<T> head)
{
    std::vector<T> res;
    while (head)
    {
        res.push_back(head->val);
        head = head->next;
    }
    return res;
}

template <typename T>
std::vector<T> to_vector_backwards(node_ptr<T> tail)
{
    std::vector<T> res;
    while (tail)
    {
        res.push_back(tail->val);
        tail = tail->prev;
    }
    return res;
}
