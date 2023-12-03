#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <regex>
#include <unordered_map>
#include <string>
#include <map>
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

std::vector<std::string> matches = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven" ,"eight", "nine"};
std::map<std::string, std::string> wordToDigit = {
    {"one", "1"},
    {"two", "2"},
    {"three", "3"},
    {"four", "4"},
    {"five", "5"},
    {"six", "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine", "9"}
};

std::string findFirst(std::string line, std::vector<std::string> matches, std::map<std::string, std::string> wordToDigit) {

    size_t minPos = SIZE_MAX;
    std::string minString = "";


    for (auto match : matches) {
        size_t pos = line.find(match);
        if (pos != std::string::npos) {
            if (pos < minPos) {
                minPos = pos;
                minString = match;
            }
        }
    }

    if (!minString.empty()) {
        if (minString.length() != 1) {
            return wordToDigit[minString];
        } else {
            return minString;
        }
    }

    throw "No match found";
}


std::string findLast(std::string line, std::vector<std::string> matches, std::map<std::string, std::string> wordToDigit) {

    std::string reversedLine = line;
    reverse(reversedLine.begin(), reversedLine.end());

    std::vector<std::string> reversedMatches = matches;
    // Reverse the content of each string entry in the vector
    for (auto& str : reversedMatches) {
        std::reverse(str.begin(), str.end());
    }

    std::map<std::string, std::string> reversedWordToDigit;;
    for (auto& pair : wordToDigit) {
        std::string key = pair.first;
        std::reverse(key.begin(), key.end());

        reversedWordToDigit.insert({key, pair.second});
    }


    return findFirst(reversedLine, reversedMatches, reversedWordToDigit);

}


int solution2() {
    std::string content =  readFile("./inputs/day1_1.txt");

    std::istringstream stringStream(content);

    std::string line;
    int sum = 0;

    while (std::getline(stringStream, line)) {

        std::string firstDigit = findFirst(line, matches, wordToDigit);
        std::string lastDigit = findLast(line, matches, wordToDigit);

        std::string value;
        value.append(firstDigit);
        value.append(lastDigit);

        int intval = std::stoi(value);
        sum += intval;
    }

    return sum;
}


int main(int argc, const char * argv[]) {

    //    std::cout << solution1() << std::endl;
    std::cout << solution2() << std::endl;

    return 0;
}
