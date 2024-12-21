#include "utils.h"


namespace Utils
{

std::ifstream loadFile(std::string_view src_path, std::string_view filename)
{
    std::string sourceFilePath{src_path};

    sourceFilePath = sourceFilePath.substr(0, sourceFilePath.find_last_of("/\\"));
    sourceFilePath += filename;

    std::ifstream inputFile{sourceFilePath};
    if (!inputFile) {
        throw std::runtime_error("Cannot open file: " + sourceFilePath);
    }

    return inputFile;
}


}