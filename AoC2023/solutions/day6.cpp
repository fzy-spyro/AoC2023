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

vector<int> parseNums(string line) {
    
    string numbersStr(line.substr(line.find(":")+1));

    std::istringstream iss(numbersStr);
    
    int num;
    vector<int> numbers;
    while (iss >> num) {
        numbers.push_back(num);
    }

    return numbers;

};

long parseNum2(string line) {

    string numbersStr(trimString((line.substr(line.find(":")+1))));

    numbersStr.erase(std::remove_if(numbersStr.begin(), numbersStr.end(), [](unsigned char c) {
        return c == ' ';
    }), line.end());

    return stol(numbersStr);

};


long countBeatingTimes(long time, long distance) {

    long current = 0;

    long sum = 0;

//    cout<< "checking (" << time << "," << distance<< ") -> ";
    while (current <= time) {

        long buttonPresTime = current;
        long raceTimeLeft = time - buttonPresTime;
        long distTravelled = raceTimeLeft * buttonPresTime;

        if (distTravelled > distance) {
//            cout << buttonPresTime << ", ";
            sum += 1;
        }
        current++;
    }

//    cout << endl;

    return sum;

}

int day6_solution1() {

    std::string content = readFile("./inputs/day6.txt");

//    cout << content << endl;

    std::istringstream stringStream(content);
    std::string timesLine;
    std::string distancesLine;

    getline(stringStream, timesLine);
    getline(stringStream, distancesLine);

    vector<int> times  = parseNums(timesLine);
    vector<int> distances  = parseNums(distancesLine);

//    cout << times << endl << distances << endl;

    int count = 1;
    for(int i = 0; i < times.size(); i++) {
        int time = times[i];
        int distance = distances[i];

        int waysToBeat = countBeatingTimes(time, distance);
//        cout << "ways to beat ("<<time << "," << distance<< ") -> " << waysToBeat << endl;
        count *= waysToBeat;
    }


    return count;
}


long day6_solution2() {

    std::string content = readFile("./inputs/day6.txt");

//    cout << content << endl;

    std::istringstream stringStream(content);
    std::string timesLine;
    std::string distancesLine;

    getline(stringStream, timesLine);
    getline(stringStream, distancesLine);

    long time = parseNum2(timesLine);
    long distance  = parseNum2(distancesLine);

    long beating = countBeatingTimes(time, distance);


    return beating;
}

int main6(int argc, const char** argv) {

    cout << day6_solution1() << endl;
    cout << day6_solution2() << endl;

    return 1;
}
