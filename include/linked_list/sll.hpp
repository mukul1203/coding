#pragma once
#include <memory>
#include <vector>

namespace sll
{
#include "node.hpp"

    template <typename T>
    struct node
    {
        T val;
        node_ptr<T> next;
        node() = default;
        node(T v) : val(std::move(v)) {}
    };

    template <typename T>
    node_ptr<T> make_list(std::initializer_list<T> list)
    {
        node_ptr<T> dummy_head(new node<T>());
        node_ptr<T> tail = dummy_head;
        for (auto &e : list)
        {
            tail->next = node_ptr<T>(new node<T>(e));
            tail = tail->next;
        }
        return dummy_head->next;
    }
}