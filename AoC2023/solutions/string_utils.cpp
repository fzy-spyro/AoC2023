#include "string_utils.hpp"

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

// Function to trim leading and trailing whitespaces from a std::string
std::string trimString(const std::string& str) {
    // Find the first non-whitespace character from the beginning
    size_t start = str.find_first_not_of(" \t\n\r");

    // If the std::string is all whitespaces, return an empty std::string
    if (start == std::string::npos) {
        return "";
    }

    // Find the last non-whitespace character from the end
    size_t end = str.find_last_not_of(" \t\n\r");

    // Extract the trimmed substd::string
    return str.substr(start, end - start + 1);
}
