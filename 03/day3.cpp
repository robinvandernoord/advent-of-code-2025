#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// part 1
int parse_line(std::string line) {
    int max_l = -1;
    int max_r = -1;

    // for (char &c : line) {
    const int len = line.length() - 1;
    for (int i = 0; i <= len; i++) {
        char &c = line[i];
        int num = c - '0'; // ASCII math

        if (num > max_l && i != len) {
            // only if this isn't the last char
            max_l = num;
            max_r = -1;
        } else if (num > max_r) {
            max_r = num;
        }
    }
    // assert(max_l != -1);
    // assert(max_r != -1);
    return max_l * 10 + max_r;
}

long part1(const std::string &filename) {
    auto file = std::ifstream(filename);

    std::string line;
    long result = 0;
    while (std::getline(file, line)) {
        result += parse_line(line);
        // assert(parse_line(line) == parse_line2(line, 2));
    }

    return result;
}

void debug_vec(std::vector<int> &vec, std::string when = "") {
    if (when != "") {
        std::cout << when << " ";
    }

    for (auto v : vec) {
        if (v == -1) {
            std::cout << ".";
        } else {
            std::cout << v;
        }
    }
    std::cout << std::endl;
}

void try_insert(std::vector<int> &vec, int value, int min_index = -1) {
    // where . is -1; one characters is one int:
    // while there's a -1 in there, try to first fill that up:
    // try_insert(..1471429, 8) -> .81471429
    // try_insert(.81471429, 3) -> 381471429
    // afterwards, increases can only start at index 0:
    // try_insert (381471429, 6) -> 638147142
    // try_insert (638147142, 5) -> 638147142

    if (min_index == -1) {
        // From right to left: if any current = -1, set value there
        for (int i = vec.size() - 1; i >= 0; i--) {
            if (vec[i] == -1) {
                vec[i] = value;
                return;
            }
        }
        // No -1 found, start swapping from left
        try_insert(vec, value, 0);
    } else {
        // From min_index onward: if value > vec[min_index], swap it
        // if the numbers are the same, try again next index (also swap for
        // convenience)
        int old_value = vec[min_index];
        if (value >= old_value && min_index < vec.size()) {
            vec[min_index] = value;
            try_insert(vec, old_value, min_index + 1);
        }
    }
}

long sum_vec(std::vector<int> vec) {
    // turn [1, 2, 3] into 123
    long result = 0;

    // index should be 0, 1, 2
    // value should be in reverse order
    for (int i = 0; i < vec.size(); i++) {
        int value = vec[vec.size() - 1 - i];
        // pow()
        result += value * pow(10, i);
    }

    return result;
}

// part 2, also works for part 1 when setting size=2
long parse_line2(std::string line, int size = 12) {
    // pre-allocate capacity 'size' with default value -1:
    auto vec = std::vector<int>(size, -1);

    // start on the right
    // first fill int[12] with tail
    // for each i remaining from the right
    // for each j in arr
    // if i > j: pop k
    // for each in rest of arr: repeat

    // iterate line by character from right to left
    for (int i = line.length() - 1; i >= 0; i--) {
        char &c = line[i];
        int num = c - '0'; // ASCII math

        // check the vector from right to left (as k)
        // if num is bigger than k at index j: pop it and go again at index j-1
        try_insert(vec, num);
    }

    // turn [1, 2, 3] into 123:
    return sum_vec(vec);
}

long part2(const std::string &filename) {
    auto file = std::ifstream(filename);

    std::string line;
    long result = 0;
    while (std::getline(file, line)) {
        result += parse_line2(line, 12);
    }

    return result;
}

void test_sum_vec() {
    auto vec = std::vector<int>();
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(1);

    assert(vec[0] == 3);
    assert(sum_vec(vec) == 321);
}

int main() {
    assert(part1("example.txt") == 357);
    const long result1 = part1("full.txt");
    std::cout << "part 1: " << result1 << std::endl;
    assert(result1 == 17445);

    test_sum_vec();

    assert(parse_line2("987654321111111") == 987654321111);
    assert(parse_line2("811111111111119") == 811111111119);
    assert(parse_line2("234234234234278") == 434234234278);
    assert(parse_line2("818181911112111") == 888911112111);

    assert(part2("example.txt") == 3121910778619);
    const long result2 = part2("full.txt");
    std::cout << "part 2: " << result2 << std::endl;
    assert(result2 == 173229689350551);

    return 0;
}
