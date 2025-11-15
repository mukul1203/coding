#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "formatting/include_all.hpp"

// Lesson:
// The below implementation can be reduced to much simpler one.
// The lesson is that for a BFS on a collection of values, we don't need to literally store the collection as a graph datastructure.
// All we need is way to find out the adjacent values to a given value. That could just be a method that figures out adjacent ones
// on demand, then those values are pushed in the queue.

std::vector<std::string> word_ladder(const std::string &start, const std::string &end, const std::unordered_set<std::string> &dict)
{
    // if end doesn't lie in dict, return empty
    // form a graph from dict, where each node is word, and its adjacent nodes are words at distance one from it
    // add the start also to this graph
    //  For each word in dict, of length k, there are only 2k possible adjacent words, so check for each if it exists in dict
    // do bfs on graph, starting at end and searching for start. To trace the path to the start, if found, we would need to
    // store the node from which any node was visited, in a hashmap, where key is the node, and value is the first visitor node.
    // looking up from start backwards to end will list the nodes in sequence

    if (dict.find(end) == dict.end())
        return {};

    // graph
    std::unordered_map<std::string, std::vector<std::string>> graph;
    const auto is_adjacent = [](const std::string &a, const std::string &b)
    {
        int count = 0;
        for (size_t i = 0; i < a.size(); ++i)
        {
            if (a[i] != b[i] && ++count && count > 1)
                return false;
        }
        return count == 1;
    };

    for (auto iter = dict.begin(); iter != dict.end(); ++iter)
    {
        if (is_adjacent(start, *iter))
        {
            graph[*iter].push_back(start);
            graph[start].push_back(*iter);
        }
        for (auto iter1 = std::next(iter); iter1 != dict.end(); ++iter1)
        {
            if (is_adjacent(*iter, *iter1))
            {
                graph[*iter].push_back(*iter1);
                graph[*iter1].push_back(*iter);
            }
        }
    }

    std::cout << graph << std::endl;

    // bfs - end to start
    std::unordered_map<std::string, std::string> visited_by;

    std::queue<std::string> q;
    q.push(end);
    visited_by[end] = "NULL";
    while (!q.empty())
    {
        auto e = q.front();
        q.pop();
        if (e == start)
            break;
        const auto &adj = graph[e];
        for (const auto &a : adj)
        {
            if (visited_by[a].empty())
            {
                q.push(a);
                visited_by[a] = e;
            }
        }
    }

    std::vector<std::string> ladder;
    auto cur = start;
    while (cur != "NULL")
    {
        ladder.push_back(cur);
        cur = visited_by[cur];
    }
    return ladder;
}

#include "test_framework/catch_amalgamated.hpp"

TEST_CASE("word ladder")
{
    std::unordered_set<std::string> dict = {"hot", "dot", "dog", "lot", "log", "cog"};
    auto ladder = word_ladder("hit", "cog", dict);
    std::cout << ladder << std::endl;
    REQUIRE((ladder[0] == "hit" && ladder[ladder.size() - 1] == "cog"));
}