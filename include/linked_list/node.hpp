#pragma once

#include <memory>
#include <vector>

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
