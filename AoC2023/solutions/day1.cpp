#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "file_reader.hpp"

int solution1() {
    std::string content =  readFile("./inputs/day1_1.txt");
    
    std::istringstream stringStream(content);
    
    std::string line;
    int sum = 0;
    
    while (std::getline(stringStream, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char c) {
            return !std::isdigit(c);
        }), line.end());
        
        if (line.empty()) continue;
        
        char firstDigit = '\0';
        char lastDigit = '\0';
        
        for (char digit : line) {
            if (firstDigit == '\0') {
                firstDigit = digit;
            }
            lastDigit = digit;
        }
        
        std::string value;
        value.append(std::string(1, firstDigit));
        value.append(std::string(1, lastDigit));
        
        //        std::cout << value << std::endl;
        
        int intval = std::stoi(value);
        sum += intval;
    }
    
    return sum;
}


int main(int argc, const char * argv[]) {
    
    std::cout << solution1() << std::endl;
    
    return 0;
}
