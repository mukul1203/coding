template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    // Use fmt::format to generate a string representation of the vector
    // and stream that string to the ostream.
    return os << fmt::format("{}", vec);
}