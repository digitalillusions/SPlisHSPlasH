//
// Created by sjeske on 1/22/20.
//
#include <SPlisHSPlasH/TimeManager.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

void TimeModule(py::module m_sub) {
    // ---------------------------------------
    // Class Time Manager
    // ---------------------------------------
    py::class_<SPH::TimeManager>(m_sub, "TimeManager")
            .def(py::init<>())
            .def_static("getCurrent", &SPH::TimeManager::getCurrent, py::return_value_policy::reference_internal)
            .def_static("setCurrent", &SPH::TimeManager::setCurrent)
            .def_static("hasCurrent", &SPH::TimeManager::hasCurrent)

            .def("getTime", &SPH::TimeManager::getTime)
            .def("setTime", &SPH::TimeManager::setTime)
            .def("getTimeStepSize", &SPH::TimeManager::getTimeStepSize)
            .def("setTimeStepSize", &SPH::TimeManager::setTimeStepSize)

            .def("saveState", &SPH::TimeManager::saveState)
            .def("loadState", &SPH::TimeManager::loadState);

}