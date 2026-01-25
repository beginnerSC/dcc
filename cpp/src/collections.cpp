#include "dcc_core/collections.h"
#include <unordered_map>
#include <string>
#include <print>

std::unordered_map<char, int> Counter(std::string_view s) {
    std::unordered_map<char, int> res;
    for (char c : s) {
        ++res[c];  // Default initializes to 0, then increments
    }
    return res;
} 