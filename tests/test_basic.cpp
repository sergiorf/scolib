
#include "scolib/scolib.hpp"
#include <cassert>
#include <iostream>

int main() {
    using namespace scolib;
    Circuit c;
    auto n0 = c.add_node();
    auto n1 = c.add_node();
    assert(n0.index == 0);
    assert(n1.index == 1);
    assert(c.node_count() == 2);
    std::cout << "SCOLIB version: " << version() << "\n";
    return 0;
}
