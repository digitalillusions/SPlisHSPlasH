//
// Created by sjeske on 1/22/20.
//
#include <SPlisHSPlasH/NonPressureForceBase.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

void NonPressureForceBaseModule(py::module m_sub) {
    py::class_<SPH::NonPressureForceBase>(m_sub, "NonPressureForceBase")
            .def("step", &SPH::NonPressureForceBase::step)
            .def("reset", &SPH::NonPressureForceBase::reset)
            .def("performNeighborhoodSearchSort", &SPH::NonPressureForceBase::performNeighborhoodSearchSort)
            .def("emittedParticles", &SPH::NonPressureForceBase::emittedParticles)
            .def("saveState", &SPH::NonPressureForceBase::saveState)
            .def("loadState", &SPH::NonPressureForceBase::loadState)
            .def("getModel", &SPH::NonPressureForceBase::getModel)
            .def("init", &SPH::NonPressureForceBase::init);
}

