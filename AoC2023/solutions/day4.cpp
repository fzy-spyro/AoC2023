#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include "file_reader.hpp"
#include "string_utils.hpp"
#include <cmath>

using namespace std;

class CardGame {
public:
    int number;
    vector<int> scratches;
    vector<int> winningNumber;
    int copies;

    int winningPoints;

    CardGame(string line) {
        copies = 1;
        winningPoints = 0;
        std::string num;
        for(auto c: line) {
            if (c == ':') break;
            if (!std::isdigit(c)) continue;
            num.append(std::string(1, c));
        }

        number = std::stoi(num);

        size_t pos = line.find(": ");
        std::string drawLine = std::string(line.begin()+pos+2, line.end());
        vector<string> drawStrings = split(drawLine, "|");

        if (drawStrings.size() < 2) throw "something wrong with input";

        auto scratchesStrings = split(trimString(drawStrings[0]), " ");
        auto winningstrings = split(trimString(drawStrings[1]), " ");


        for(auto s: scratchesStrings) {
            scratches.push_back(stoi(s));
        }
        for(auto s: winningstrings) {
            winningNumber.push_back(stoi(s));
        }

        sort(scratches.begin(), scratches.end());
        sort(winningNumber.begin(), winningNumber.end());
    }

    int countPoints() {

        vector<int> res;
        std::set_intersection(scratches.begin(), scratches.end(), winningNumber.begin(), winningNumber.end(), std::back_inserter(res));

        return pow(2, res.size()-1);
    }

    int countPoints2() {
        vector<int> res;
        std::set_intersection(scratches.begin(), scratches.end(), winningNumber.begin(), winningNumber.end(), std::back_inserter(res));
        winningPoints = res.size();
        return winningPoints;
    }


};

int day4_solution1() {
    std::string content = readFile("./inputs/day4.txt");

    std::istringstream stringStream(content);
    std::string line;

    std::vector<CardGame> games;

    while (std::getline(stringStream, line)) {
        games.push_back(CardGame(line));
    }

    int sum = 0;
    for (auto game: games) {
        sum += game.countPoints();
    }

    return sum;
}

int day4_solution2() {
    std::string content = readFile("./inputs/day4_test.txt");

    std::istringstream stringStream(content);
    std::string line;

    std::vector<CardGame> games;

    while (std::getline(stringStream, line)) {
        CardGame game(line);
        game.countPoints2();
        games.push_back(game);
    }

    int processedScratchCards = 0;
    for(int i = 0; i< games.size(); i++) {
        while (games[i].copies > 0) {
            processedScratchCards += 1;
            for (int j = 1; j <= games[i].winningPoints; j++) {
                games[i+j].copies += 1;
            }
            games[i].copies -= 1;
        }
    }

//    int sum = 0;
//    for(auto g: games) {
//        sum += g.copies;
//    }

    return processedScratchCards;
}


int main4(int argc, const char * argv[]) {
//    std::cout<< day4_solution1() << endl ;
        std::cout<< day4_solution2() << endl ;
    return 0;
}
