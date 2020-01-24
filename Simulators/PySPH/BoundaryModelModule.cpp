//
// Created by sjeske on 1/23/20.
//
#include <SPlisHSPlasH/BoundaryModel.h>
#include <SPlisHSPlasH/BoundaryModel_Akinci2012.h>

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <SPlisHSPlasH/BoundaryModel_Bender2019.h>
#include <SPlisHSPlasH/BoundaryModel_Koschier2017.h>

namespace py = pybind11;

template <typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;

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

    // ---------------------------------------
    // Boundary Model Akinci 2012
    // ---------------------------------------
    py::class_<SPH::BoundaryModel_Akinci2012, SPH::BoundaryModel>(m_sub, "BoundaryModelAkinci2012")
            .def(py::init<>())
            .def("numberOfParticles", &SPH::BoundaryModel_Akinci2012::numberOfParticles)
            .def("getPointSetIndex", &SPH::BoundaryModel_Akinci2012::getPointSetIndex)
            .def("computeBoundaryVolume", &SPH::BoundaryModel_Akinci2012::computeBoundaryVolume)
            .def("resize", &SPH::BoundaryModel_Akinci2012::resize)
            .def("reset", &SPH::BoundaryModel_Akinci2012::reset)
            .def("performNeighborhoodSearchSort", &SPH::BoundaryModel_Akinci2012::performNeighborhoodSearchSort)
            .def("saveState", &SPH::BoundaryModel_Akinci2012::saveState)
            .def("loadState", &SPH::BoundaryModel_Akinci2012::loadState)
            .def("initModel", &SPH::BoundaryModel_Akinci2012::initModel)
            .def("getPosition0", (Vector3r& (SPH::BoundaryModel_Akinci2012::*)(const unsigned int))(&SPH::BoundaryModel_Akinci2012::getPosition0))
            .def("getPosition0", (const Vector3r& (SPH::BoundaryModel_Akinci2012::*)(const unsigned int) const)(&SPH::BoundaryModel_Akinci2012::getPosition0))
            .def("setPosition0", &SPH::BoundaryModel_Akinci2012::setPosition0)
            .def("getPosition", (Vector3r& (SPH::BoundaryModel_Akinci2012::*)(const unsigned int))(&SPH::BoundaryModel_Akinci2012::getPosition))
            .def("getPosition", (const Vector3r& (SPH::BoundaryModel_Akinci2012::*)(const unsigned int) const)(&SPH::BoundaryModel_Akinci2012::getPosition))
            .def("setPosition", &SPH::BoundaryModel_Akinci2012::setPosition)
            .def("getVelocity", (Vector3r& (SPH::BoundaryModel_Akinci2012::*)(const unsigned int))(&SPH::BoundaryModel_Akinci2012::getVelocity))
            .def("getVelocity", (const Vector3r& (SPH::BoundaryModel_Akinci2012::*)(const unsigned int) const)(&SPH::BoundaryModel_Akinci2012::getVelocity))
            .def("setVelocity", &SPH::BoundaryModel_Akinci2012::setVelocity)
            .def("getVolume", (Real& (SPH::BoundaryModel_Akinci2012::*)(const unsigned int))(&SPH::BoundaryModel_Akinci2012::getVolume))
            .def("getVolume", (const Real& (SPH::BoundaryModel_Akinci2012::*)(const unsigned int) const)(&SPH::BoundaryModel_Akinci2012::getVolume))
            .def("setVolume", &SPH::BoundaryModel_Akinci2012::setVolume);

    // ---------------------------------------
    // Boundary Model Bender 2019
    // ---------------------------------------
    py::class_<SPH::BoundaryModel_Bender2019, SPH::BoundaryModel>(m_sub, "BoundaryModelBender2019")
            .def(py::init<>())
            .def("initModel", &SPH::BoundaryModel_Bender2019::initModel)
            .def("reset", &SPH::BoundaryModel_Bender2019::reset)
            .def("getMap", &SPH::BoundaryModel_Bender2019::getMap)
            .def("setMap", &SPH::BoundaryModel_Bender2019::setMap)
            .def("getMaxDist", &SPH::BoundaryModel_Bender2019::getMaxDist)
            .def("setMaxDist", &SPH::BoundaryModel_Bender2019::setMaxDist)
            .def("getMaxVel", &SPH::BoundaryModel_Bender2019::getMaxVel)
            .def("setMaxVel", &SPH::BoundaryModel_Bender2019::setMaxVel)
            .def("getBoundaryVolume", (const Real& (SPH::BoundaryModel_Bender2019::*)(const unsigned int, const unsigned int)const)(&SPH::BoundaryModel_Bender2019::getBoundaryVolume))
            .def("getBoundaryVolume", (Real& (SPH::BoundaryModel_Bender2019::*)(const unsigned int, const unsigned int))(&SPH::BoundaryModel_Bender2019::getBoundaryVolume))
            .def("setBoundaryVolume", &SPH::BoundaryModel_Bender2019::setBoundaryVolume)
            .def("getBoundaryXj", (const Vector3r& (SPH::BoundaryModel_Bender2019::*)(const unsigned int, const unsigned int)const)(&SPH::BoundaryModel_Bender2019::getBoundaryXj))
            .def("getBoundaryXj", (Vector3r& (SPH::BoundaryModel_Bender2019::*)(const unsigned int, const unsigned int))(&SPH::BoundaryModel_Bender2019::getBoundaryXj))
            .def("setBoundaryXj", &SPH::BoundaryModel_Bender2019::setBoundaryXj);

    // ---------------------------------------
    // Boundary Model Koschier 2017
    // ---------------------------------------
    py::class_<SPH::BoundaryModel_Koschier2017, SPH::BoundaryModel>(m_sub, "BoundaryModelKoschier2017")
            .def(py::init<>())
            .def("initModel", &SPH::BoundaryModel_Koschier2017::initModel)
            .def("reset", &SPH::BoundaryModel_Koschier2017::reset)
            .def("getMap", &SPH::BoundaryModel_Koschier2017::getMap)
            .def("setMap", &SPH::BoundaryModel_Koschier2017::setMap)
            .def("getMaxDist", &SPH::BoundaryModel_Koschier2017::getMaxDist)
            .def("setMaxDist", &SPH::BoundaryModel_Koschier2017::setMaxDist)
            .def("getMaxVel", &SPH::BoundaryModel_Koschier2017::getMaxVel)
            .def("setMaxVel", &SPH::BoundaryModel_Koschier2017::setMaxVel)
            .def("getBoundaryDensity", (const Real & (SPH::BoundaryModel_Koschier2017::*)(const unsigned int, const unsigned int)const)(&SPH::BoundaryModel_Koschier2017::getBoundaryDensity))
            .def("getBoundaryDensity", (Real & (SPH::BoundaryModel_Koschier2017::*)(const unsigned int, const unsigned int))(&SPH::BoundaryModel_Koschier2017::getBoundaryDensity))
            .def("setBoundaryDensity", &SPH::BoundaryModel_Koschier2017::setBoundaryDensity)
            .def("getBoundaryDensityGradient", (const Vector3r& (SPH::BoundaryModel_Koschier2017::*)(const unsigned int, const unsigned int)const)(&SPH::BoundaryModel_Koschier2017::getBoundaryDensityGradient))
            .def("getBoundaryDensityGradient", (Vector3r& (SPH::BoundaryModel_Koschier2017::*)(const unsigned int, const unsigned int))(&SPH::BoundaryModel_Koschier2017::getBoundaryDensityGradient))
            .def("setBoundaryDensityGradient", &SPH::BoundaryModel_Koschier2017::setBoundaryDensityGradient)
            .def("getBoundaryXj", (const Vector3r& (SPH::BoundaryModel_Koschier2017::*)(const unsigned int, const unsigned int)const)(&SPH::BoundaryModel_Koschier2017::getBoundaryXj))
            .def("getBoundaryXj", (Vector3r& (SPH::BoundaryModel_Koschier2017::*)(const unsigned int, const unsigned int))(&SPH::BoundaryModel_Koschier2017::getBoundaryXj))
            .def("setBoundaryXj", &SPH::BoundaryModel_Koschier2017::setBoundaryXj);
}
