#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int part1(const std::string &filename) {
    auto file = std::ifstream(filename);

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    return 0;
}

int part2(const std::string &filename) {
    return 0;
}

int main() {
    assert(part1("example.txt") == 0); // change me
    const int result1 = part1("full.txt");
    printf("part 1: %d\n", result1);
    assert(result1 == 0); // change me

    // assert(part2("example.txt") == 0); // change me
    // const int result2 = part2("full.txt");
    // printf("part 2: %d\n", result2);
    // assert(result2 == 0); // change me

    return 0;
}
