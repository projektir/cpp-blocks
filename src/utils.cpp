#include "utils.hpp"

bool operator<(XY a, XY b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}
