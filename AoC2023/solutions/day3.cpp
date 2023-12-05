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


enum AdjacentDirection {
    up_left = 0,
    up,
    up_right,
    left,
    right,
    bottom_left,
    bottom,
    bottom_right
};

map<AdjacentDirection, vector<int>> day3_directionMappings = {
    { AdjacentDirection::up_left, {-1, -1} },
    { AdjacentDirection::up, {-1, 0} },
    { AdjacentDirection::up_right, {-1, 1} },
    { AdjacentDirection::left, {0, -1} },
    { AdjacentDirection::right, {0, 1} },
    { AdjacentDirection::bottom_left, {1, -1} },
    { AdjacentDirection::bottom, {1, 0} },
    { AdjacentDirection::bottom_right, {1, 1} },
};

vector<AdjacentDirection> checkAdjacent2(int row, int col, int MAX_ROWS, int MAX_COLS, const vector<vector<char>> &inputMap) {

    vector<AdjacentDirection> adjacents;

    // Check up left
    if (row - 1 >= 0 && col - 1 >= 0 && isdigit(inputMap[row - 1][col - 1])) {
        adjacents.push_back(AdjacentDirection::up_left);
    }

    // Check up
    if (row - 1 >= 0 && isdigit(inputMap[row - 1][col])) {
//        if (find(adjacents.begin(), adjacents.end(), AdjacentDirection::up_left) == adjacents.end()) {
            adjacents.push_back(AdjacentDirection::up);
//        }
    }

    if (row - 1 >= 0 && col + 1 < MAX_COLS && isdigit(inputMap[row - 1][col + 1])) {
//        if (find(adjacents.begin(), adjacents.end(), AdjacentDirection::up) == adjacents.end()) {
            adjacents.push_back(AdjacentDirection::up_right);
//        }
    }

    // Check left
    if (col - 1 >= 0 && isdigit(inputMap[row][col - 1])) {
        adjacents.push_back(AdjacentDirection::left);
    }

    // Check right
    if (col + 1 < MAX_COLS && isdigit(inputMap[row][col + 1])) {
        adjacents.push_back(AdjacentDirection::right);
    }

    if (row + 1 < MAX_ROWS && col - 1 >= 0 && isdigit(inputMap[row + 1][col - 1])) {
        adjacents.push_back(AdjacentDirection::bottom_left);
    }

    // Check below
    if (row + 1 < MAX_ROWS && isdigit(inputMap[row + 1][col])) {
//        if (find(adjacents.begin(), adjacents.end(), AdjacentDirection::bottom_left) == adjacents.end()) {
            adjacents.push_back(AdjacentDirection::bottom);
//        }
    }

    if (row + 1 < MAX_ROWS && col + 1 < MAX_COLS && isdigit(inputMap[row + 1][col + 1])) {
//        if (find(adjacents.begin(), adjacents.end(), AdjacentDirection::bottom) == adjacents.end()) {
            adjacents.push_back(AdjacentDirection::bottom_right);
//        }
    }

    return adjacents;


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

vector<int> findAdjacentNumbers(int row, int col, int rows, int cols, vector<vector<char>> &inputMap) {
    vector<int> numbers;

    auto directions = checkAdjacent2(row, col, rows, cols, inputMap);
//    if (directions.size() != 2) {
//        return numbers;
//    }

    for(auto dir: directions) {
        int startX = row + day3_directionMappings[dir][0];
        int startY = col + day3_directionMappings[dir][1];

        while(isdigit(inputMap[startX][startY]) && startY > 0 && isdigit(inputMap[startX][startY-1])) {
            startY -= 1;
        }

        string num;
        while(isdigit(inputMap[startX][startY]) && startY < cols) {
            num.append(string(1, inputMap[startX][startY]));
            inputMap[startX][startY] = '.';
            startY++;
        }

        if (!num.empty()) {
            numbers.push_back(stoi(num));
        }
    }

    return numbers;
}

int day3_solution2() {
    
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

    const int rows = i;
    const int cols = inputMap[0].size();
    int sum = 0;

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            char value = inputMap[x][y];

            if (value == '*') {
                vector<int> gearNums = findAdjacentNumbers(x, y, rows, cols, inputMap);
                if (gearNums.size() == 2) {
                    sum += (gearNums[0] * gearNums[1]);
                }
            }

        }
    }

    return sum;
}


int main3(int argc, const char * argv[]) {
//    std::cout<< day3_solution1() << endl ;
    std::cout<< day3_solution2() << endl ; // too low ???
    return 0;
}
