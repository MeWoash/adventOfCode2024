#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace Utils
{

std::ifstream loadFile(std::string_view src_path, std::string_view filename);

}


