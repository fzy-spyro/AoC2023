//

#ifndef string_utils_hpp
#define string_utils_hpp

#include <iostream>
#include <string>
#include <vector>

std::string trimString(const std::string& str);
std::vector<std::string> split(const std::string& str, const std::string& delim);


// Overload the << operator for vector
template <typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        os << *it;
        if (it + 1 != vec.end()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif /* string_utils_hpp */
