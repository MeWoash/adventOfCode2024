#include <iostream>

#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <map>
#include <string_view>
#include "utils.h"

static bool foo(int a, int b)
{
    int diff{abs(a-b)};
    return (diff<1 || diff > 3);
}

std::vector<int> copyVectorWithoutIndex(const std::vector<int>& vector, size_t index)
{
    std::vector<int> new_vec{vector};
    new_vec.erase(new_vec.begin()+index);
    return new_vec;
}

static bool isSafe(const std::vector<int>& vector)
{
    auto begin{vector.begin()};
    auto end{vector.end()};

    auto found{std::adjacent_find(begin, end, foo)};

    bool is_sorted_incr{std::is_sorted(begin, end, std::less{})};
    bool is_sorted_decr{std::is_sorted(begin, end, std::greater{})};
    bool adj_valid{found == end};
    bool is_safe{adj_valid && (is_sorted_incr || is_sorted_decr)};

    // std::cout<<vector
    // <<" is_safe: "<<is_safe
    // <<", incr: "<<is_sorted_incr
    // <<", decr: "<<is_sorted_decr
    // <<", adj: "<<adj_valid
    // <<", found: "<<static_cast<ptrdiff_t>(found - begin)<<"\n";

    return is_safe;
}

void part1(std::vector<std::vector<int>> vector)
{
    u_int64_t safe_reports{};
    
    for (const auto& row : vector)
    {
        if (isSafe(row))
        {
            safe_reports++;
        }
    }
    std::cout<<"Valid reports: "<<safe_reports<<"\n";
    
}

void part2(std::vector<std::vector<int>> vector)
{
    u_int64_t safe_reports{};
    
    for (const auto& row : vector)
    {
        if (isSafe(row))
        {
            safe_reports++;
        }
        else
        {
            for (size_t i{0}; i<row.size(); i++)
            {
                if (isSafe(copyVectorWithoutIndex(row, i)))
                {
                    safe_reports++;
                    break;
                }
            }
        }
    }
    std::cout<<"Valid reports: "<<safe_reports<<"\n";
    
}

int main()
{
    auto inputFile{Utils::loadFile(__FILE__, "/input.txt")};
    auto vector{Utils::loadValues<int>(inputFile)};
    inputFile.close();

    // std::cout<<vector;
    Utils::timeIt([&vector](){part1(vector);}, 10);
    Utils::timeIt([&vector](){part2(vector);}, 10);
    
    
}