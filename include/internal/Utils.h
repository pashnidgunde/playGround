#pragma once
#include <vector>
#include <ostream>

std::ostream& operator << (std::ostream &os, std::vector<int> &v) {
    for (const auto &e: v) {
        os << e << ",";
    }
    return os;
}
