#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int parse_instruction(std::string line) {
    const auto first = line.front();
    line.erase(0, 1);
    int value = std::atoi(line.c_str());

    if (first == 'L') {
        value *= -1;
    }

    return value;
}

int apply_delta(const int original_value, const int delta) {
    const int wrapped_value = (original_value + delta) % 100;
    return wrapped_value < 0 ? wrapped_value + 100 : wrapped_value;
}

int apply_delta2(int *mut_value, const int delta) {
    const int prev = *mut_value;
    int seen_zero = abs(delta) / 100; // initial wraps
    *mut_value += delta % 100;

    int wrapped_times = 0;
    while (*mut_value > 99) {
        *mut_value -= 100;
        wrapped_times++;
    }

    while (*mut_value < 0) {
        *mut_value += 100;
        wrapped_times++;
    }

    if (*mut_value != 0 && prev != 0) {
        seen_zero += wrapped_times;
    } else if (*mut_value == 0) {
        seen_zero++;
    }

    return seen_zero;
}

int part1(const std::string &filename) {
    auto file = std::ifstream(filename);

    int result = 50;
    int seen_zero = 0;

    std::string line;
    while (std::getline(file, line)) {
        const int delta = parse_instruction(line);
        // result = apply_delta(result, delta);
        apply_delta2(&result, delta);
        // std::cout << "result:" << result << std::endl;
        if (result == 0) {
            seen_zero++;
        }
    }

    return seen_zero;
}


int part2(const std::string &filename) {
    auto file = std::ifstream(filename);

    int result = 50;
    int seen_zero = 0;

    std::string line;
    while (std::getline(file, line)) {
        const int delta = parse_instruction(line);
        seen_zero += apply_delta2(&result, delta);
    }

    return seen_zero;
}

int main() {
    assert(part1("example.txt") == 3);
    const int result1 = part1("full.txt");
    assert(result1 == 997);
    printf("part 1: %d\n", result1);

    assert(part2("example.txt") == 6);
    const int result2 = part2("full.txt");
    assert(result2 == 5978);
    printf("part 2: %d\n", result2);

    return 0;
}
