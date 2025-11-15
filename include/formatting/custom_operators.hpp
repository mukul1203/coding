#pragma once

#include <vector>
#include <unordered_map>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &val)
{
    // Use fmt::format to generate a string representation of the vector
    // and stream that string to the ostream.
    return os << fmt::format("{}", val);
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &val)
{
    // Use fmt::format to generate a string representation of the vector
    // and stream that string to the ostream.
    return os << fmt::format("{}", val);
}