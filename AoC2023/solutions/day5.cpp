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
#include <cassert>
#include <memory>
#include "file_reader.hpp"
#include "string_utils.hpp"

using namespace std;

class Range {
public:
    long destinationStart;
    long sourceStart;
    long count;

    Range(string line) {
        std::istringstream iss(line);

        // Vector to store the extracted numbers
        std::vector<long> numbers;

        // Read numbers from the string stream
        long num;
        while (iss >> num) {
            numbers.push_back(num);
        }

        assert(numbers.size() == 3);

        destinationStart = numbers[0];
        sourceStart = numbers[1];
        count = numbers[2];
    }


    long getDestination(long source) {

        if (source>= sourceStart && source<= (sourceStart+count)) {
            long sourcePos = source - sourceStart;
            return destinationStart + sourcePos;
        }

        return  -1;
    }
};

class AlmanacMapping {
public:
    string name;
    vector<Range> ranges;

    AlmanacMapping(string input) {
        name = input;
    }

    void addRange(string line) {
        ranges.push_back(Range(line));
    }

    long findMapping(long input) {
        long result = -1;
        for(auto r: ranges) {
            result = r.getDestination(input);
            if (result != -1) break;
        }

        if (result == -1) {
            return input;
        }

        return result;

    }
};

long day5_solution1() {

    std::string content = readFile("./inputs/day5.txt");

    std::istringstream stringStream(content);
    std::string line;

    string seedsLine;
    vector<std::unique_ptr<AlmanacMapping>> mappings;

    int current = 0;
    bool isParsingMapping = false;
    unique_ptr<AlmanacMapping> currentMapping;

    while (std::getline(stringStream, line)) {
        if (seedsLine.empty()) {
            seedsLine = line;
            continue;
        }

        if (isParsingMapping && line.empty()) {
            isParsingMapping = false;
            current++;
            continue;
        }

        if (line[line.length()-1] == ':') { //start new mapping
            mappings.push_back(make_unique<AlmanacMapping>(line));
            isParsingMapping = true;
            continue;
        }

        if (isParsingMapping) {
            mappings[current].get()->addRange(line);
        }
    }

    // data parsed and we can now find locations
    long minLocation = LONG_MAX;
    string seedsNumber(seedsLine.substr(seedsLine.find(": ")+2));

    std::istringstream iss(seedsNumber);
    long seed;
    while (iss >> seed) {

        long result = seed;
        cout << "start: " << result;
        for(auto &m: mappings) {
            cout << " -> ";
            result = m.get()->findMapping(result);
            cout << result;
        }

        cout<<endl;
        minLocation = min(result, minLocation);

    }

    return minLocation;
}


// brute force - takes > 1h to solve ;) 
long day5_solution2() {

    std::string content = readFile("./inputs/day5.txt");

    std::istringstream stringStream(content);
    std::string line;

    string seedsLine;
    vector<std::unique_ptr<AlmanacMapping>> mappings;

    int current = 0;
    bool isParsingMapping = false;
    unique_ptr<AlmanacMapping> currentMapping;

    while (std::getline(stringStream, line)) {
        if (seedsLine.empty()) {
            seedsLine = line;
            continue;
        }

        if (isParsingMapping && line.empty()) {
            isParsingMapping = false;
            current++;
            continue;
        }

        if (line[line.length()-1] == ':') { //start new mapping
            mappings.push_back(make_unique<AlmanacMapping>(line));
            isParsingMapping = true;
            continue;
        }

        if (isParsingMapping) {
            mappings[current].get()->addRange(line);
        }
    }

    // data parsed and we can now find locations
    long minLocation = LONG_MAX;
    string seedsNumber(seedsLine.substr(seedsLine.find(": ")+2));

    std::istringstream iss(seedsNumber);
    long seedStart, count;
    while (iss >> seedStart >> count) {

        for(long seed = seedStart; seed < seedStart + count; seed++) {
            long result = seed;
//            cout << "start: " << result;
            for(auto &m: mappings) {
//                cout << " -> ";
                result = m.get()->findMapping(result);
//                cout << result;
            }

//            cout<<endl;

            minLocation = min(result, minLocation);
        }
    }

    return minLocation;
}


int main5(int argc, const char * argv[]) {
//    std::cout<< day5_solution1() << endl ;
        std::cout<< day5_solution2() << endl ;
    return 0;
}
