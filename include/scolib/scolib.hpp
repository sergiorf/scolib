
#pragma once

#include <string>

namespace scolib {

// Library version string (semantic version)
std::string version();

// Placeholder core API for future SPICE-lite
struct NodeID { int index = -1; };

class Circuit {
public:
    Circuit() = default;
    NodeID add_node();
    int node_count() const noexcept;

private:
    int nodes_ = 0;
};

} // namespace scolib
