#include <iostream>

#include <fstream>
#include <vector>
#include <string>


static void loadFile()
{   
    std::string sourceFilePath{__FILE__};

    sourceFilePath = sourceFilePath.substr(0, sourceFilePath.find_last_of("/\\"));
    sourceFilePath += "/input.txt";

    std::ifstream inputFile(sourceFilePath);
    if (!inputFile) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }

    std::vector<int> list1{}, list2{};
    std::string val1{}, val2{};

    while (inputFile >> val1 >> val2) {
        list1.push_back(std::stoi(val1));
        list2.push_back(std::stoi(val2));
    }

    inputFile.close();
    std::cout<<list1.size();
}

int main()
{
    loadFile();
}