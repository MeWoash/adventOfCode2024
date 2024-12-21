#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

namespace Utils
{

std::ifstream loadFile(std::string_view src_path, std::string_view filename);

template <typename T>
std::vector<std::vector<T>> loadValues(std::ifstream& ifstream)
{  
    std::vector<std::vector<T>> vector{};
    std::string line{};

    while (std::getline(ifstream, line))
    {
        std::istringstream stream{line};
        std::vector<T> row{};
        
        T value{};
        while (stream >> value)
        {
            row.push_back(value);
        }
        vector.push_back(std::move(row));
    }

    return vector;
    
}

}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v)
{
    os<<"[ ";
    for (const auto& val: v)
    {
        os<<val<<" ";
    }
    os<<"] N: "<<v.size()<<"\n";
    return os;
}
