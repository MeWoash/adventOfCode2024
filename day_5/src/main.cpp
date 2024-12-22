#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <string_view>
#include "utils.h"
#include <algorithm>
#include <map>

constexpr char delimiterInRuleset{'|'};


template <typename T, typename N>
std::ostream& operator<<(std::ostream& os, std::map<T, N> map)
{
    for (const auto& [key, value]: map)
    {
        os<<key<<" -> "<<value<<"\n";
    }
    return os;
}

bool isUpdateValid(const std::map<int, std::vector<int>>& ruleset, const std::vector<int>& update)
{
    auto it{update.rbegin()};
    auto end{update.rend()};
    
    for (;it != end-1; it++)
    {
        auto val{*it};

        for (auto it_cmp{it+1}; it_cmp != end; it_cmp++)
        {
            auto val_cmp{*it_cmp};
            // std::cout<<val<<" & "<<val_cmp<<"\n";
            std::cout<<"comparing: "<<val<<" "<<val_cmp<<"\n";
            if (ruleset.contains(val_cmp))
            {
                const auto& values{ruleset.at(val_cmp)};
                if (std::find(values.begin(), values.end(), val) == values.end())
                {
                    std::cout<<"Update: "<<update<<" value: "<<val<<" val_cmp: "<<val_cmp<<"\n";
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        
    }
    return true;
}

void part1([[maybe_unused]]const std::map<int, std::vector<int>>& ruleset, const std::vector<std::vector<int>>& updates)
{

    for (const auto& update : updates)
    {
        isUpdateValid(ruleset, update);
    }
}

int main()
{
    
    auto file{Utils::loadFile(__FILE__, "/input_test.txt")};
    
    std::map<int, std::vector<int>> ruleset{};
    std::string line{};
    
    while(std::getline(file,line))
    {
        if(line.empty())
        {
            break;
        }
        std::stringstream ss{line};

        char delimiter{};
        int left{}, right{};
        if ((ss >> left >> delimiter >> right) && delimiter == delimiterInRuleset)
        {
            ruleset[left].push_back(right);
        }
    }

    auto updates{Utils::loadValues<int>(file, ',')};

    std::cout<<ruleset;
    std::cout<<updates;

    part1(ruleset, updates);
    
}