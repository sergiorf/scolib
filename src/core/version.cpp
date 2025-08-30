
#include "scolib/scolib.hpp"
#include "scolib/version.hpp"
#include <sstream>

namespace scolib {

std::string version() {
    std::ostringstream oss;
    oss << SCOLIB_VERSION_MAJOR << "."
        << SCOLIB_VERSION_MINOR << "."
        << SCOLIB_VERSION_PATCH;
    return oss.str();
}

} // namespace scolib
