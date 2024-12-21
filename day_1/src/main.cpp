#include <iostream>

#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <map>
#include <string_view>
#include "utils.h"

void part1(std::vector<int> list1, std::vector<int> list2)
{
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    u_int64_t dist{};

    for (size_t index{0}; index<list1.size(); index++)
    {
        dist += abs(list1[index] - list2[index]);
    }

    std::cout<<"distance: "<<dist<<"\n";
}

void part2(std::vector<int> list1, std::vector<int> list2)
{
    std::map<int, int> freq{};
    
    for (const auto& el : list2)
    {
        freq[el]++;
    }

    u_int64_t sim_score{};
    for (const auto& num : list1)
    {
        if (freq.contains(num))
        {
            sim_score+= num*freq[num];
        }
    }
    std::cout<<"sim score: "<<sim_score<<"\n";
}

int main()
{
    std::ifstream inputFile{Utils::loadFile(__FILE__, "/input.txt")};

    std::vector<int> list1{}, list2{};
    std::string val1{}, val2{};

    while (inputFile >> val1 >> val2) {
        list1.push_back(std::stoi(val1));
        list2.push_back(std::stoi(val2));
    }

    inputFile.close();

    part1(list1, list2);
    part2(list1, list2);
    
    
}