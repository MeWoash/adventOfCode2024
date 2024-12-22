#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <utility>

namespace Utils
{

std::ifstream loadFile(std::string_view src_path, std::string_view filename);

template <typename T>
std::vector<std::vector<T>> loadValues(std::ifstream& fin, char delimiter = ',')
{  
    std::vector<std::vector<T>> result;
    std::string line;

    while (std::getline(fin, line))
    {
        if (line.empty()) {
            break;
        }
        
        std::vector<T> row{};
        std::istringstream stream(line);
        std::string token{};
        
        while (std::getline(stream, token, delimiter))
        {
            if (!token.empty())
            {
                std::istringstream tokenStream(token);
                T value{};
                tokenStream >> value;
                row.push_back(value);
            }
        }
        result.push_back(std::move(row));
    }

    return result;
}

template <typename Func, typename Unit = std::chrono::nanoseconds>
typename Unit::rep timeIt(Func&& func, int n_runs = 1) {
    
    typename Unit::rep total_duration{0};
    
    for (int run = 0; run < n_runs; ++run) {
        auto start = std::chrono::high_resolution_clock::now();
        std::forward<Func>(func)();
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<Unit>(end - start).count();
        total_duration += duration;
    }

    auto avg_duration{total_duration / n_runs};
    std::cout << std::setprecision(10) << "AVG Time of function: " << avg_duration << " units\n";

    return avg_duration;
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
