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

void part1(std::vector<std::vector<int>> vector)
{
    u_int64_t safe_reports{};
    for (const auto& row : vector)
    {
        auto begin{row.begin()};
        auto end{row.end()};

        auto found{std::adjacent_find(begin, end, foo)};

        bool is_sorted_incr{std::is_sorted(begin, end, std::less{})};
        bool is_sorted_decr{std::is_sorted(begin, end, std::greater{})};
        bool adj_valid{found == end};

        bool is_safe{adj_valid && (is_sorted_incr || is_sorted_decr)};
        if(is_safe)
        {
            safe_reports++;
        }
        std::cout<<row\
        <<" is_safe: "<<is_safe\
        <<", incr: "<<is_sorted_incr\
        <<", decr: "<<is_sorted_decr\
        <<", adj: "<<adj_valid\
        <<", found: "<<static_cast<ptrdiff_t>(found - begin)<<"\n";
    }

    std::cout<<"Valid reports: "<<safe_reports<<"\n";
    
}

int main()
{
    auto inputFile{Utils::loadFile(__FILE__, "/input.txt")};
    auto vector{Utils::loadValues<int>(inputFile)};
    inputFile.close();

    // std::cout<<vector;
    part1(vector);
    
    
}