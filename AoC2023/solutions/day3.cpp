#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include <map>
#include "file_reader.hpp"
#include "string_utils.hpp"

using namespace std;

bool isSymbol(char c) {
    return c != '.' && !isdigit(c);
}


bool checkAdjacent(int row, int col, int MAX_ROWS, int MAX_COLS, const vector<vector<char>> &inputMap) {

    // Check left
    if (col - 1 >= 0 && isSymbol(inputMap[row][col - 1])) {
        return true;
    }

    // Check right
    if (col + 1 < MAX_COLS && isSymbol(inputMap[row][col + 1])) {
        return true;
    }

    // Check above
    if (row - 1 >= 0 && isSymbol(inputMap[row - 1][col])) {
        return true;
    }

    // Check below
    if (row + 1 < MAX_ROWS && isSymbol(inputMap[row + 1][col])) {
        return true;
    }

    // Check diagonals
    if (row - 1 >= 0 && col - 1 >= 0 && isSymbol(inputMap[row - 1][col - 1])) {
        return true;
    }

    if (row - 1 >= 0 && col + 1 < MAX_COLS && isSymbol(inputMap[row - 1][col + 1])) {
        return true;
    }

    if (row + 1 < MAX_ROWS && col - 1 >= 0 && isSymbol(inputMap[row + 1][col - 1])) {
        return true;
    }

    if (row + 1 < MAX_ROWS && col + 1 < MAX_COLS && isSymbol(inputMap[row + 1][col + 1])) {
        return true;
    }

    return false;


}


int day3_solution1() {

    string content = readFile("./inputs/day3.txt");
    std::istringstream stringStream(content);
    std::string line;

    vector<vector<char>> inputMap;

    int i = 0;
    while (std::getline(stringStream, line)) {
        vector<char> chars;
        inputMap.push_back(chars);
        for(auto s: line) {
            inputMap[i].push_back(s);
        }
        i++;
    }

    int rows = i;
    int cols = inputMap[0].size();

    bool hasContinuousNumber = false;
    bool isAdjacent = false;
    string lastNum;

    int sum = 0;

    for(int x = 0; x < rows; x++) {

        if (hasContinuousNumber) {
            if (isAdjacent) {
                int numValue = stoi(lastNum);
                lastNum = "";
                sum += numValue;
            }
        }
        hasContinuousNumber = false;
        isAdjacent = false;
        lastNum = "";

        for(int y = 0; y < cols; y++) {
            char value = inputMap[x][y];

            if (!isdigit(value)) {
                if (hasContinuousNumber) {
                    if (isAdjacent) {
                        int numValue = stoi(lastNum);
                        lastNum = "";
                        sum += numValue;
                    }
                }
                hasContinuousNumber = false;
                isAdjacent = false;
                lastNum = "";
            } else {
                hasContinuousNumber = true;
                lastNum.append(string(1, value));
                isAdjacent |= checkAdjacent(x,y, rows, cols, inputMap);
            }
        }

    }

    return sum;
}


int main(int argc, const char * argv[]) {
    std::cout<< day3_solution1() << endl ;
    //    std::cout<< day2_solution2() << endl ;
    return 0;
}
