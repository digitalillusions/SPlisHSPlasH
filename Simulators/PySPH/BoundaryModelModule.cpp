//
// Created by sjeske on 1/23/20.
//
#include <SPlisHSPlasH/BoundaryModel.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

void BoundaryModelModule(py::module m_sub){
    // ---------------------------------------
    // Boundary Model
    // ---------------------------------------
    py::class_<SPH::BoundaryModel>(m_sub, "BoundaryModel")
            .def(py::init<>())
            .def("reset", &SPH::BoundaryModel::reset)
            .def("performNeighborhoodSearchSort", &SPH::BoundaryModel::performNeighborhoodSearchSort)
            .def("saveState", &SPH::BoundaryModel::saveState)
            .def("loadState", &SPH::BoundaryModel::loadState)
            .def("getRigidBodyObject", &SPH::BoundaryModel::getRigidBodyObject)
            .def("addForce", &SPH::BoundaryModel::addForce)
            .def("getPointVelocity", &SPH::BoundaryModel::getPointVelocity)
            .def("getForceAndTorque", &SPH::BoundaryModel::getForceAndTorque)
            .def("clearForceAndTorque", &SPH::BoundaryModel::clearForceAndTorque);

}
