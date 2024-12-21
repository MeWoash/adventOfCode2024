#include <iostream>

#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <map>
#include <string_view>
#include <regex>
#include "utils.h"

void part1(const std::string& input)
{
    std::regex pattern{R"(mul\((\d+)\,(\d+)\))"};

    std::vector<std::pair<int, int>> results{};

    auto it{std::sregex_iterator(input.begin(), input.end(), pattern)};
    auto end{std::sregex_iterator()};

    while (it!=end)
    {
        std::smatch matches{*it};
        int val1{std::stoi(matches[1])};
        int val2{std::stoi(matches[2])};
        results.emplace_back(val1, val2);
        it++;
    }

    std::cout<<"Found: "<<results.size()<<" entries\n";

    uint64_t sum{};

    for (const auto& pair : results)
    {
        sum+= pair.first * pair.second;
    }
    std::cout<<"sum: "<<sum<<"\n";

}

void part2(const std::string& input)
{
    std::regex pattern_replace{R"(don\'t\(\)[\s\S]*?do\(\))"};
    std::regex pattern_replace2{R"(don\'t\(\)[\s\S]*?$)"};

    std::string replaced{std::regex_replace(input, pattern_replace, "")};
    replaced = std::regex_replace(replaced, pattern_replace2, "");
    std::cout<<replaced;

    std::regex pattern{R"(mul\((\d+)\,(\d+)\))"};

    std::vector<std::pair<int, int>> results{};

    auto it{std::sregex_iterator(replaced.begin(), replaced.end(), pattern)};
    auto end{std::sregex_iterator()};

    while (it!=end)
    {
        std::smatch matches{*it};
        int val1{std::stoi(matches[1])};
        int val2{std::stoi(matches[2])};
        results.emplace_back(val1, val2);
        it++;
    }

    std::cout<<"Found: "<<results.size()<<" entries\n";

    uint64_t sum{};

    for (const auto& pair : results)
    {
        sum+= pair.first * pair.second;
    }
    std::cout<<"sum: "<<sum<<"\n";

}

int main()
{
    
    auto file{Utils::loadFile(__FILE__, "/input_test.txt")};
    std::ostringstream buffer;
    buffer << file.rdbuf();
    auto input{buffer.str()};

    Utils::timeIt([&input](){part1(input);}, 1);
    Utils::timeIt([&input](){part2(input);}, 1);
    
}