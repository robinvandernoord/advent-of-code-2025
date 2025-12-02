#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

long part1(const std::string &filename) {
    auto file = std::ifstream(filename);

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    return 0;
}

long part2(const std::string &filename) {
    return 0;
}

int main() {
    assert(part1("example.txt") == 0); // change me
    const long result1 = part1("full.txt");
    std::cout << "part 1: " << result1 << std::endl;
    assert(result1 == 0); // change me

    // assert(part2("example.txt") == 0); // change me
    // const long result2 = part2("full.txt");
    // std::cout << "part 2: " << result2 << std::endl;
    // assert(result2 == 0); // change me

    return 0;
}
