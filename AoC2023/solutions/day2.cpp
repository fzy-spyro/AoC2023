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
#include "string_utils.hpp"

using namespace std;

class Draw {
public:
    int red = 0;
    int green = 0;
    int blue = 0;


    Draw(string line) {
        vector<string> draws = split(line, ",");

        for(auto d : draws) {
            string draw = trimString(d);
            vector<string> balls = split(draw, " ");
            if (balls[1] == "red") {
                red = stoi(balls[0]);
            }

            if (balls[1] == "green") {
                green = stoi(balls[0]);
            }

            if (balls[1] == "blue") {
                blue = stoi(balls[0]);
            }
        }
    }

    bool isPossible(int maxRed, int maxGreen, int maxBlue) {
        return red <= maxRed && green <= maxGreen && blue <= maxBlue;
    }
};

class Game {
public:
    int number;
    std::vector<Draw> draws;

    Game(std::string line) {
        std::string num;
        for(auto c: line) {
            if (c == ':') break;
            if (!std::isdigit(c)) continue;
            num.append(std::string(1, c));
        }
        
        number = std::stoi(num);

        size_t pos = line.find(": ");
        std::string drawLine = std::string(line.begin()+pos+2, line.end());
        vector<string> drawStrings = split(drawLine, ";");

        for(auto d: drawStrings) {
            draws.push_back(Draw(d));
        }

    }

    bool isPossible(int maxRed, int maxGreen, int maxBlue) {
        bool isPossible = true;
        for(auto game: draws) {
            isPossible &= game.isPossible(maxRed, maxGreen, maxBlue);
        }
        return isPossible;
    }

    int powerSet() {
        int minRed, minGreen, minBlue;
        minRed = minGreen = minBlue = 0;

        int total = 0;
        for(auto draw: draws) {
            minRed = max(minRed, draw.red);
            minGreen = max(minGreen, draw.green);
            minBlue = max(minBlue, draw.blue);
        }
        int power = minRed * minGreen * minBlue;
        return power;
    }

};

int day2_solution1() {
    std::string content = readFile("./inputs/day2.txt");

    std::istringstream stringStream(content);
    std::string line;

    std::vector<Game> games;


    while (std::getline(stringStream, line)) {
        games.push_back(Game(line));
    }

    int sum = 0;
//    cout << games.size() << endl;
    for (auto game: games) {
        if (game.isPossible(12, 13, 14)) {
            sum += game.number;;
        }
    }

    return sum;
}

int day2_solution2() {
    std::string content = readFile("./inputs/day2.txt");

    std::istringstream stringStream(content);
    std::string line;

    std::vector<Game> games;


    while (std::getline(stringStream, line)) {
        games.push_back(Game(line));
    }

    int sum = 0;
    for (auto game: games) {
        sum += game.powerSet();
    }

    return sum;
}

int main2(int argc, const char * argv[]) {
//    std::cout<< day2_solution1() << endl ;
    std::cout<< day2_solution2() << endl ;
    return 0;
}
