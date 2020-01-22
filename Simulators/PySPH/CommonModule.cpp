//
// Created by sjeske on 1/22/20.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;

void CommonModule(py::module m){
    auto m_sub = m.def_submodule("Common");
}
