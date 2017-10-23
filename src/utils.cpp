#include "utils.hpp"

bool operator<(XY a, XY b) {
    return std::make_pair(a.x, a.y) < std::make_pair(b.x, b.y);
}
