//
// Created by sjeske on 1/28/20.
//

#include <pybind11/pybind11.h>

#include <iostream>

namespace py = pybind11;

struct ForceBase{
    virtual void step() = 0;
};

struct Force : public ForceBase {
    virtual void step(){
        std::cout << "Hello" << std::endl;
    }
};

void do_step(ForceBase* force){
    force->step();
}

PYBIND11_MODULE(PyTest, m){
    py::class_<ForceBase>(m, "ForceBase")
            .def("step", &ForceBase::step);

    py::class_<Force, ForceBase>(m, "Force")
            .def(py::init<>());

    m.def("do_step", &do_step);

}
