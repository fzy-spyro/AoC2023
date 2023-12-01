#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "file_reader.hpp"


int main2(int argc, const char * argv[]) {

    std::string content =  readFile("./inputs/day2_1.txt");

    std::cout<< "day 2 " << content;
    return 0;
}
