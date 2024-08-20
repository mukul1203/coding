#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <cassert>

template <typename T>
struct circular_queue
{
    circular_queue(size_t n)
    {
        _q.resize(n);
    }

    [[nodiscard]] bool empty() const
    {
        return _size == 0;
    }

    size_t capacity() const
    {
        return _q.capacity();
    }

    size_t size() const
    {
        return _size;
    }

    [[nodiscard]] bool full() const
    {
        return _size == capacity();
    }

    void enqueue(T val)
    {
        if (full())
        {
            std::rotate(_q.begin(), _q.begin() + _front, _q.end());
            _front = 0;
            _rear = size();
            _q.resize(capacity() * 2);
        }
        _q[_rear] = std::move(val);
        _rear = (_rear + 1) % capacity();
        ++_size;
    }

    T dequeue()
    {
        assert(!empty());
        T val = _q[_front];
        _front = (_front + 1) % capacity();
        --_size;
        return val;
    }

private:
    std::vector<T> _q;
    size_t _front{0}, _rear{0};
    size_t _size{0};
};

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("circular queue")
{
    auto cq = circular_queue<char>(5);
    for (const auto &c : std::string("hell"))
        cq.enqueue(c);
    REQUIRE(cq.size() == 4);
    REQUIRE(cq.capacity() == 5);
    cq.enqueue('o');
    REQUIRE(cq.size() == 5);
    REQUIRE(cq.capacity() == 5);
    cq.enqueue('w');
    REQUIRE(cq.size() == 6);
    auto c = cq.capacity();
    REQUIRE(c == 10);
    std::string s;
    while (!cq.empty())
    {
        s.push_back(cq.dequeue());
    }
    REQUIRE(s == "hellow");
    REQUIRE(cq.size() == 0);
    REQUIRE(cq.capacity() == c);
    REQUIRE(cq.empty());

    s += "orld";
    for (const auto &c : s)
    {
        cq.enqueue(c);
    }
    REQUIRE(cq.size() == 10);
    REQUIRE(cq.capacity() == 10);

    REQUIRE(cq.dequeue() == 'h');
    REQUIRE(cq.size() == 9);
    REQUIRE(cq.capacity() == 10);

    cq.enqueue('!');
    REQUIRE(cq.size() == 10);
    REQUIRE(cq.capacity() == 10);

    cq.dequeue(); // e
    cq.dequeue(); // l
    cq.enqueue('@');
    cq.enqueue('#');
    cq.enqueue('$');
    REQUIRE(cq.size() == 11);
    REQUIRE(cq.capacity() == 20);

    s.clear();
    while (!cq.empty())
    {
        s.push_back(cq.dequeue());
    }
    REQUIRE(s == "loworld!@#$");
}