#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#define point std::pair<int, int>

long calculate_times(const std::vector<long> &numbers) {
    long result = 1;

    for (const auto num: numbers) {
        result *= num;
    }

    return result;
}

long calculate_plus(const std::vector<long> &numbers) {
    long result = 0;

    for (const auto num: numbers) {
        result += num;
    }
    return result;
}

long calculate(const std::vector<long> &numbers, const char &operation) {
    if (operation == '*') {
        return calculate_times(numbers);
    } else {
        return calculate_plus(numbers);
    }
}

long part1(const std::string &filename) {
    auto file = std::ifstream(filename);

    auto numbers = std::vector<std::vector<long> >();
    long result = 0;

    std::string line;
    while (std::getline(file, line)) {
        int idx = 0;
        std::string segment;
        auto line_stream = std::stringstream(line);
        while (std::getline(line_stream, segment, ' ')) {
            if (segment.empty()) {
                continue;
            }

            if (segment == "*" || segment == "+") {
                result += calculate(numbers[idx], segment[0]);
            } else {
                // else: normal number
                auto num = atol(segment.c_str());

                if (idx == numbers.size()) {
                    auto new_vec = std::vector<long>();
                    numbers.push_back(new_vec);
                }

                numbers[idx].push_back(num);
            }


            idx++;
        }
    }

    return result;
}

template<typename T>
void dbg_vec(const std::vector<T> &vec) {
    std::cout << "[";
    for (const auto v: vec) {
        std::cout << v << ",";
    }

    std::cout << "]" << std::endl;
}

long part2(const std::string &filename) {
    auto file = std::ifstream(filename);

    int max_row = 0;
    int max_col = 0;

    auto map = std::map<point, char>();

    std::string line;
    while (std::getline(file, line)) {
        int col = 0;

        for (auto c: line) {
            if (c != ' ') {
                auto p = point(col, max_row);
                map[p] = c;
            }

            col++;
        }
        if (max_row == 0 && max_col == 0) {
            max_col = col;
        }

        max_row++;
    }

    // 1 2
    // 3 4
    // + *
    // ->
    // 1 3 +
    // 2 4 *

    long result = 0;

    auto queue = std::vector<long>();

    // print map 90°, right-to-left by column (end block with operation):
    for (int x = max_col; x >= 0; x--) {
        long cur_num = 0;

        for (int y = 0; y < max_row; y++) {
            auto p = point(x, y);
            auto c = map[p];

            if (c == '\0') {
                continue;
            }

            if (c == '*' || c == '+') {
                queue.push_back(cur_num);
                // dbg_vec(queue);
                result += calculate(queue, c);
                queue.clear();
                cur_num = 0; // prevent re-using last number
                continue;
            }

            int num = c - '0'; // ASCII math

            cur_num = cur_num * 10 + num;
        }

        if (cur_num) {
            queue.push_back(cur_num);
        }
    }

    return result;
}

int main() {
    assert(part1("example.txt") == 4277556);
    const long result1 = part1("full.txt");
    std::cout << "part 1: " << result1 << std::endl;
    assert(result1 == 4309240495780);

    assert(part2("example.txt") == 3263827);
    const long result2 = part2("full.txt");
    std::cout << "part 2: " << result2 << std::endl;
    assert(result2 == 9170286552289);

    return 0;
}
