
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "scolib/scolib.hpp"

namespace py = pybind11;
using namespace scolib;

PYBIND11_MODULE(scolib, m) {
    m.doc() = "SCOLIB Python bindings (minimal)";

    m.def("version", &version, "Get SCOLIB version string");

    py::class_<NodeID>(m, "NodeID")
        .def_readonly("index", &NodeID::index);

    py::class_<Circuit>(m, "Circuit")
        .def(py::init<>())
        .def("add_node", &Circuit::add_node)
        .def("node_count", &Circuit::node_count);
}
