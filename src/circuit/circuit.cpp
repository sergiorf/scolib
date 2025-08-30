
#include "scolib/scolib.hpp"

namespace scolib {

NodeID Circuit::add_node() {
    NodeID id{nodes_};
    ++nodes_;
    return id;
}

int Circuit::node_count() const noexcept {
    return nodes_;
}

} // namespace scolib
