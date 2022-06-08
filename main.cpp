#include <iostream>
#include <string>
#include "PathTool.hpp"

int main()
{
    std::string str_path = "/usr/bin/cmake";
    std::string str_parent_path = tools::PathTool::find_parent_folder(str_path);
    std::cout << str_parent_path << std::endl;
    return 0;
}