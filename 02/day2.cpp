#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

bool check_invalid(const size_t i) {
    const auto candidate = std::to_string(i);

    const auto len = candidate.size();
    const auto idx_half = len / 2;

    const auto left = candidate.substr(0, idx_half);
    const auto right = candidate.substr(idx_half, len);

    return left == right;
}

size_t part1(const std::string &filename) {
    auto file = std::ifstream(filename);

    size_t result = 0;

    std::string line;
    while (std::getline(file, line, ',')) {
        const auto left_c = strtok(line.data(), "-");
        const auto right_c = strtok(NULL, "-");

        const size_t left = atol(left_c);
        const size_t right = atol(right_c);

        for (size_t i = left; i <= right; i++) {
            if (check_invalid(i)) {
                // std::cout << i << std::endl;
                result += i;
            }
        }
    }
    return result;
}

const static auto pattern = std::regex("^(\\d+)\\1+$");

bool check_invalid_repeating(const size_t i) {
    // (\d+)\1
    const auto candidate = std::to_string(i);

    return std::regex_search(candidate, pattern);
}

size_t part2(const std::string &filename) {
    auto file = std::ifstream(filename);

    size_t result = 0;

    std::string line;
    while (std::getline(file, line, ',')) {
        const auto left_c = strtok(line.data(), "-");
        const auto right_c = strtok(NULL, "-");

        const size_t left = atol(left_c);
        const size_t right = atol(right_c);

        for (size_t i = left; i <= right; i++) {
            if (check_invalid_repeating(i)) {
                // std::cout << i << std::endl;
                result += i;
            }
        }
    }
    return result;
}

int main() {
    assert(part1("example.txt") == 1227775554);
    const size_t result1 = part1("full.txt");
    std::cout << "part 1: " << result1 << std::endl;
    assert(result1 == 40214376723);

    assert(part2("example.txt") == 4174379265);
    const size_t result2 = part2("full.txt");
    std::cout << "part 2: " << result2 << std::endl;
    assert(result2 == 50793864718);

    return 0;
}
