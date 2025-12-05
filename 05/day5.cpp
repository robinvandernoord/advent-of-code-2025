#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define range std::pair<long, long>
#define v_ranges std::vector<range>

range parse_range(std::string &line) {
    auto left = atol(strtok(line.data(), "-"));
    auto right = atol(strtok(NULL, "-"));

    return range(left, right);
}

bool check_in_range(long num, v_ranges &ranges) {
    for (auto r : ranges) {
        auto [start, end] = r;
        if (start <= num && num <= end) {
            return true;
        }
    }
    return false;
}

static const range SENTINEL_RANGE = range(-1, -1);

long part1(const std::string &filename) {
    auto file = std::ifstream(filename);

    bool switched = false;
    auto ranges = v_ranges();
    long result = 0;

    std::string line;
    while (std::getline(file, line)) {
        if (line == "") {
            switched = true;
        } else if (switched) {
            long num = atol(line.c_str());
            if (check_in_range(num, ranges)) {
                result++;
            }

        } else {
            ranges.push_back(parse_range(line));
        }
    }
    return result;
}

long part2(const std::string &filename) {
    auto file = std::ifstream(filename);

    long result = 0;
    auto ranges = v_ranges();

    std::string line;
    while (std::getline(file, line)) {
        if (line == "") {
            break;
        }
        ranges.push_back(parse_range(line));
    }

    // 1. sort ranges (range[0] now has the lowest start)
    sort(ranges.begin(), ranges.end());

    range previous_range = SENTINEL_RANGE; // pointer is annoying here so use a
                                           // sentinal instead of NULL

    // 2. check if ranges[1] falls within range[0]
    //    -> extend
    //    else: count size of range[0] and repeat
    for (auto current_range : ranges) {
        if (previous_range == SENTINEL_RANGE) {
            // first iteration
            previous_range = current_range;
        } else {
            if (previous_range.second >= current_range.first) {
                if (current_range.second > previous_range.second) {
                    previous_range.second = current_range.second;
                } // else: sub range, skip
            } else {
                // update result
                result += (previous_range.second - previous_range.first) + 1;
                previous_range = current_range;
            }
        }
    }
    // final one
    result += (previous_range.second - previous_range.first) + 1;

    return result;
}

int main() {
    assert(part1("example.txt") == 3);
    const long result1 = part1("full.txt");
    std::cout << "part 1: " << result1 << std::endl;
    assert(result1 == 690);

    assert(part2("example.txt") == 14);
    const long result2 = part2("full.txt");
    std::cout << "part 2: " << result2 << std::endl;
    assert(result2 == 344323629240733);

    return 0;
}
