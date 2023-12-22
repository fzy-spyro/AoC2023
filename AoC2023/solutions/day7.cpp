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

enum HandType {
    highCard = 0,
    pair,
    twoPairs,
    threeOfAKind,
    fullHouse,
    fourOfAKind,
    fiveOfAKind
};

class Hand {
public:
    string cards;
    long bid;
    HandType type;

    Hand(string line) {
        vector<string> splitted = split(line, " ");
        cards = splitted[0];
        bid = stol(splitted[1]);

        type = determineType(splitted[0]);
    }


private:
    HandType determineType(string cards) {
        map<char, int> cardHeatMap;
        for(auto c: cards) {
            if (cardHeatMap.contains(c)) {
                cardHeatMap[c] = cardHeatMap[c] + 1;
            } else {
                cardHeatMap[c] = 1;
            }
        }

        switch (cardHeatMap.size()) {
            case 1: return HandType::fiveOfAKind;
            case 2:  {
                // fullhouse or for of a kind
                int maxCount = -1;
                for(auto &e: cardHeatMap) {
                    maxCount = max(maxCount, e.second);
                }

                if (maxCount == 4) return HandType::fourOfAKind;

                return HandType::fullHouse;
            }
            case 3: {
                //two pairs or three of a kind
                int maxCount = -1;
                for(auto &e: cardHeatMap) {
                    maxCount = max(maxCount, e.second);
                }

                if (maxCount == 3) return HandType::threeOfAKind;

                return HandType::twoPairs;
            }
            case 4: return HandType::pair;
            case 5: return HandType::highCard;
            }

            throw "Unexpected!";
        }

};

int order(char c) {
    switch (c) {
        case 'A': return 100;
        case 'K': return 99;
        case 'Q': return 98;
        case 'J': return 97;
        case 'T': return 96;
        case '9': return 95;
        case '8': return 94;
        case '7': return 93;
        case '6': return 92;
        case '5': return 91;
        case '4': return 90;
        case '3': return 89;
        case '2': return 88;
    }

    throw "unexpected symbol";
};


// Custom comparator to sort strings by length
bool handComparator(const Hand lhs, const Hand& rhs) {
    if (lhs.type == rhs.type) {

        for(int i = 0; i < lhs.cards.size(); i++) {
            int l = order(lhs.cards[i]);
            int r = order(rhs.cards[i]);


            if (l == r) continue;

            return l < r;

        }


    } else {
        return lhs.type < rhs.type;
    }

    return false;
}



int day7_solution1() {
    std::string content = readFile("./inputs/day7.txt");

    std::istringstream stringStream(content);
    std::string line;

    vector<Hand> hands;
    while (std::getline(stringStream, line)) {
        hands.push_back(Hand(line));
    }


    std::sort(hands.begin(), hands.end(), handComparator);

    for(auto &h: hands) {
        cout << h.type << " " << h.cards << " " << h.bid << endl;
    }

    int rank = 1;
    int sum = 0;
    for (auto &h: hands) {
        sum += rank * h.bid;
        rank++;
    }

    return sum;

}


long day7_solution2() {

    return -1;
}

int main(int argc, const char** argv) {

    cout << day7_solution1() << endl;
    cout << day7_solution2() << endl;

    return 1;
}
