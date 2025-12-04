#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define point std::pair<int, int>
#define pointmap std::map<point, bool>

bool check_point(point p0, pointmap &pm, int max = 3) {
    auto [x0, y0] = p0;

    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        int x1 = x0 + dx;
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) {
                // = p0, skip
                continue;
            }

            int y1 = y0 + dy;

            auto p1 = point(x1, y1);
            if (pm[p1]) {
                count++;
            }
        }
    }

    return count <= max;

    // 8 combinations:
    // x - 1, x, x + 1
    // y - 1, y, y + 1
}

pointmap build_pointmap(const std::string &filename) {
    auto file = std::ifstream(filename);

    // mapping of pair<x,y> = bool (sparse)
    auto map = pointmap();

    std::string line;
    int x = 0;
    while (std::getline(file, line)) {
        for (int y = 0; y < line.length(); y++) {
            char &c = line[y];
            point p = point(x, y);

            if (c == '@') {
                map[p] = true;
            }
        }
        x++;
    }
    return map;
}

long part1(const std::string &filename) {
    auto map = build_pointmap(filename);

    int success = 0;
    // map is filled, start checks:
    for (auto const &[key, val] : map) {
        if (val && check_point(key, map)) {
            success++;
        }
    }

    return success;
}

long part2(const std::string &filename) {
    auto map = build_pointmap(filename);

    int cnt_removed = 0;

    auto to_be_removed = std::vector<point>();

    do {
        // runs at least once
        to_be_removed.clear();

        for (auto const &[key, val] : map) {
            if (val && check_point(key, map)) {
                to_be_removed.push_back(key);
            }
        }

        cnt_removed += to_be_removed.size();

        for (point key : to_be_removed) {
            map[key] = false;
            // std::cout << "kill" << x << "," << y << std::endl;
        }

        // fixme: only remove here

    } while (to_be_removed.size() > 0);

    return cnt_removed;
}

int main() {
    assert(part1("example.txt") == 13);
    const long result1 = part1("full.txt");
    std::cout << "part 1: " << result1 << std::endl;
    assert(result1 == 1537);

    assert(part2("example.txt") == 43);
    const long result2 = part2("full.txt");
    std::cout << "part 2: " << result2 << std::endl;
    assert(result2 == 8707);

    return 0;
}
