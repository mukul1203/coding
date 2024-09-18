#include <string>
#include <cstdint>
#include <fstream>
#include <filesystem>
#include <set>
#include <optional>
#include <vector>
#include <queue>
#include <functional>
#include <sstream>
#include <random>

constexpr std::uint32_t CHUNK_SIZE = 1'000; // in bytes

struct info
{
    long long time_stamp{0}; // in milliseconds
    std::string stock_symbol{};
    std::uint32_t num_of_stocks{0};
    double stock_price{0.0};

    // returns bytes read, or nullopt if EOF reached
    std::optional<std::uint32_t> read_from(std::istream &file)
    {
        if (file.eof())
            return std::nullopt;
        auto start = file.tellg();
        std::string s;
        std::getline(file, s);
        if (s.empty())
            return std::nullopt;
        std::stringstream ss(s);
        std::string e;
        std::getline(ss, e, ',');
        time_stamp = std::stoll(e);
        e.erase();
        std::getline(ss, stock_symbol, ',');
        std::getline(ss, e, ',');
        num_of_stocks = std::stoi(e);
        e.erase();
        std::getline(ss, e);
        stock_price = std::stod(e);
        return file.tellg() - start; // TODO: handle error case by returning nullopt
    }

    // returns bytes written, or nullopt in case of any error
    std::optional<std::uint32_t> write_to(std::ostream &file) const
    {
        std::streampos start = file.tellp();
        file << time_stamp << "," << stock_symbol << "," << num_of_stocks << "," << stock_price << std::endl;
        return file.tellp() - start; // TODO: handle error case by returning nullopt
    }

    friend bool operator<(const info &a, const info &b)
    {
        return a.time_stamp < b.time_stamp;
    }
};

std::fstream make_sorted_temp_file(std::ifstream &in_file, const std::filesystem::path &temp_file_path)
{
    // Stores tuples from a chunk
    std::set<info> data;
    // Read chunk-size worth of tuples
    info d;
    auto start = in_file.tellg();
    auto cur_pos = start;
    while (auto bytes_read = d.read_from(in_file))
    {
        if (in_file.tellg() - start > CHUNK_SIZE)
        {
            // break, and restore the file pos to the start of the line read
            in_file.seekg(cur_pos);
            break;
        }
        cur_pos = in_file.tellg();
        data.insert(std::move(d));
    }

    std::fstream temp_file(temp_file_path, std::ios::in | std::ios::out | std::ios::trunc); // trunc to create a file if it doesn't exist, if exists, then truncate to zero length
    if (temp_file.is_open())
    {
        for (const auto &t : data)
        {
            auto bytes_written = t.write_to(temp_file);
        }
    }
    temp_file.seekg(0);
    return temp_file;
}

void sort_and_write(const std::filesystem::path &in_file_path, const std::filesystem::path &out_file_path)
{
    std::uint32_t temp_file_counter = 0;

    // List of sorted temp file streams, one per chunk
    std::vector<std::fstream> temp_files;

    std::ifstream in_file(in_file_path, std::ios::in);
    if (in_file.is_open())
    {
        while (in_file)
        {
            auto temp_file_path = in_file_path.parent_path() / (std::string("temp") + std::to_string(++temp_file_counter) + in_file_path.filename().string());
            temp_files.push_back(make_sorted_temp_file(in_file, temp_file_path));
        }
    }

    std::ofstream out_file(out_file_path, std::ios::out | std::ios::trunc);
    if (out_file.is_open())
    {
        // Merge temp files and write to out file
        using qentry = std::pair<info, std::reference_wrapper<std::fstream>>;
        using qentry_comparator_t = std::function<bool(const qentry &, const qentry &)>;
        // priority queue is a max heap always i.e. it always keeps the maximum element at top, maximum being defined by the comparator.
        // Comparator defines an ordering of elements. Here we are ordering them greater to smaller i.e. if a > b, then a comes before b.
        // priority queue then gives the last element (the maximum) as top(), which now becomes the actual minimum timestamp.
        std::priority_queue<qentry, std::vector<qentry>, qentry_comparator_t> min_heap([](const qentry &a, const qentry &b)
                                                                                       { return b.first < a.first; });
        for (auto &temp : temp_files)
        {
            info d;
            if (d.read_from(temp))
                min_heap.push({std::move(d), temp});
        }

        while (!min_heap.empty())
        {
            auto [d, stream] = min_heap.top(); // TODO: need non const reference, but getting a copy
            min_heap.pop();
            // write the min value to out file
            if (d.write_to(out_file))
            {
                // read the next value from the same stream which gave the min value
                // and push it in heap
                if (auto bytes_read = d.read_from(stream))
                    min_heap.push({std::move(d), stream});
            }
        }
    }
}

std::filesystem::path generate_test_file_with_random_data()
{
    static auto rng = [](int i, int j) -> int
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return std::uniform_int_distribution<>(i, j)(gen);
    };
    std::filesystem::path test_file_path = "test.txt";
    std::ofstream test_file(test_file_path);
    for (int i = 0; i < 1000; ++i)
    {
        info d;
        // a random integer (timestamp)
        d.time_stamp = rng(0, 100000000);
        // a random four character word (stock symbol)
        int n = 4;
        while (n--)
        {
            d.stock_symbol += char(rng('a', 'z'));
        }
        // a random integer (number of stocks)
        d.num_of_stocks = rng(1, 50);
        // a random integer (price of stock)
        d.stock_price = rng(1, 500);
        d.write_to(test_file);
    }
    return test_file_path;
}

bool is_sorted(const std::filesystem::path &file_path)
{
    std::ifstream file(file_path);
    if (file.is_open())
    {
        info prev;
        if (prev.read_from(file))
        {
            while (file)
            {
                info cur;
                if (cur.read_from(file))
                {
                    if (cur.time_stamp < prev.time_stamp)
                        return false;
                    prev = cur;
                }
            }
        }
    }
    return true;
}

#include "formatting/include_all.hpp"
#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("sort a large file")
{
    auto input_file_path = generate_test_file_with_random_data();
    sort_and_write(input_file_path, "sorted.txt");
    REQUIRE(is_sorted("sorted.txt") == true);
}