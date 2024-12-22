#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <string_view>
#include "utils.h"
#include <algorithm>


uint64_t countSubstrings(const std::string& input, std::string_view word)
{
    uint64_t count{};
    size_t pos{input.find(word, 0)};
    while (pos != std::string::npos)
    {
        count++;
        pos = input.find(word, pos+1);
    }
    return count;
}

static uint64_t countHorizontaly(const std::vector<std::string>& input, std::vector<std::string> words)
{
    uint64_t count{};
    for (const auto& word : words)
    {
        for (const auto& row : input)
        {
            count += countSubstrings(row, word);
        }
    } 
    return count;
}

static uint64_t searchVerticaly(const std::vector<std::string>& input, std::vector<std::string> words)
{
    uint64_t count{};
    size_t max_cols{input[0].size()};
    size_t max_rows{input.size()};

    for (size_t col_idx{}; col_idx<max_cols; col_idx++)
    {   
        std::string column_str{};
        for (size_t row_idx{}; row_idx < max_rows; row_idx++)
        {
            column_str += input[row_idx][col_idx];
        }

        for (const auto& word : words)
        {
            count += countSubstrings(column_str, word);
        }

    }
    return count;
}

static uint64_t searchDiagonaly(const std::vector<std::string>& input, [[maybe_unused]] std::vector<std::string> words)
{
    uint64_t count{0};
    if (input.empty()) {
        return count;
    }
    int max_rows{static_cast<int>(input.size())};
    int max_cols{static_cast<int>(input[0].size())};
    for(int d{0}; d < max_rows + max_cols - 1; ++d) {
        int startRow{d < max_rows ? d : max_rows - 1};
        int startCol{d < max_rows ? 0 : d - (max_rows - 1)};
        int row{startRow};
        int col{startCol};
        std::string line_str{};
        while(row >= 0 && col < max_cols) {
            line_str += input[row][col];
            --row;
            ++col;
        }
        for(const auto& word : words) {
            count += countSubstrings(line_str, word);
        }
    }
    for(int d{0}; d < max_rows + max_cols - 1; ++d) {
        int startRow{d < max_cols ? max_rows - 1 : max_rows - 1 - (d - (max_cols - 1))};
        int startCol{d < max_cols ? d : max_cols - 1};
        int row{startRow};
        int col{startCol};
        std::string line_str{};
        while(row >= 0 && col >= 0) {
            line_str += input[row][col];
            --row;
            --col;
        }
        for(const auto& word : words) {
            count += countSubstrings(line_str, word);
        }
    }
    return count;
}

void part1(const std::vector<std::string>& input, std::string_view word)
{
    std::vector<std::string> words{std::string(word), {word.rbegin(), word.rend()}};


    uint64_t count{};
    count += countHorizontaly(input, words);
    count += searchVerticaly(input, words);
    count += searchDiagonaly(input, words);

    std::cout<<"Words found: "<<count<<"\n";
}

void part2(const std::vector<std::string>& input)
{
    uint64_t count{};
    int max_rows{static_cast<int>(input.size())};
    int max_cols{static_cast<int>(input[0].size())};

    const std::vector<std::string>& words{"MSAMS", "MMASS", "SMASM", "SSAMM"};

    constexpr size_t pattern_rows{3};
    constexpr size_t pattern_cols{3};

    for (size_t row{0}; row < max_rows - pattern_rows + 1; row++)
    {
        for (size_t col{0}; col < max_cols - pattern_cols + 1; col++)
        {
            std::string in_str{
                input[row][col],
                input[row][col+2],
                input[row+1][col+1],
                input[row+2][col],
                input[row+2][col+2],
            };
            // std::cout<<row<<" "<<col<<" "<<in_str<<"\n";

            for ( const auto& word : words)
            {
                word==in_str ? count++: count;
            }
        }
    }
    std::cout<<"count: "<<count<<"\n";
}


int main()
{
    
    auto file{Utils::loadFile(__FILE__, "/input.txt")};
    
    std::vector<std::string> vector{};

    std::string line{};
    while (std::getline(file, line))
    {
        vector.push_back(std::move(line));
    }

    part1(vector, "XMAS");
    part2(vector); // hardcoded
    // Utils::timeIt([&input](){part1(input);}, 1);

    
}