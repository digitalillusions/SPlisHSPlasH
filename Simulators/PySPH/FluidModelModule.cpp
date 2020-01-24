//
// Created by sjeske on 1/22/20.
//
#include <SPlisHSPlasH/FluidModel.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

namespace py = pybind11;

void FluidModelModule(py::module m_sub){
    // ---------------------------------------
    // Enum Field Type
    // ---------------------------------------
    py::enum_<SPH::FieldType>(m_sub, "FieldType")
            .value("Scalar", SPH::FieldType::Scalar)
            .value("Vector3", SPH::FieldType::Vector3)
            .value("Vector6", SPH::FieldType::Vector6)
            .value("Matrix3", SPH::FieldType::Matrix3)
            .value("Matrix6", SPH::FieldType::Matrix6)
            .value("UInt", SPH::FieldType::UInt);

    // ---------------------------------------
    // Struct Field Description
    // ---------------------------------------
    py::class_<SPH::FieldDescription>(m_sub, "FieldDescription")
            .def(py::init<>([](const std::string &n, const SPH::FieldType &t,
                               const std::function<void*(const unsigned int)> &fct, const bool s = false){
                return SPH::FieldDescription(n, t, fct, s);
            }))
            .def_readwrite("name", &SPH::FieldDescription::name)
            .def_readwrite("type", &SPH::FieldDescription::type)
            .def_readwrite("getFct", &SPH::FieldDescription::getFct)
            .def_readwrite("storeData", &SPH::FieldDescription::storeData);

    // ---------------------------------------
    // Enum class Surface Tension Methods
    // ---------------------------------------
    py::enum_<SPH::SurfaceTensionMethods>(m_sub, "SurfaceTensionMethods")
            .value("None", SPH::SurfaceTensionMethods::None)
            .value("Becker2007", SPH::SurfaceTensionMethods::Becker2007)
            .value("Akinci2013", SPH::SurfaceTensionMethods::Akinci2013)
            .value("He2014", SPH::SurfaceTensionMethods::He2014)
            .value("NumSurfaceTensionMethods", SPH::SurfaceTensionMethods::NumSurfaceTensionMethods);

    // ---------------------------------------
    // Enum class Viscosity Methods
    // ---------------------------------------
    py::enum_<SPH::ViscosityMethods >(m_sub, "ViscosityMethods")
            .value("None", SPH::ViscosityMethods::None)
            .value("Standard", SPH::ViscosityMethods::Standard)
            .value("XSPH", SPH::ViscosityMethods::XSPH)
            .value("Bender2017", SPH::ViscosityMethods::Bender2017)
            .value("Peer2015", SPH::ViscosityMethods::Peer2015)
            .value("Peer2016", SPH::ViscosityMethods::Peer2016)
            .value("Takahashi2015", SPH::ViscosityMethods::Takahashi2015)
            .value("Weiler2018", SPH::ViscosityMethods::Weiler2018)
            .value("NumViscosityMethods", SPH::ViscosityMethods::NumViscosityMethods);

    // ---------------------------------------
    // Enum class Vorticity Methods
    // ---------------------------------------
    py::enum_<SPH::VorticityMethods>(m_sub, "VorticityMethods")
            .value("None", SPH::VorticityMethods::None)
            .value("Micropolar", SPH::VorticityMethods::Micropolar)
            .value("VorticityConfinement", SPH::VorticityMethods::VorticityConfinement)
            .value("NumVorticityMethods", SPH::VorticityMethods::NumVorticityMethods);

    // ---------------------------------------
    // Enum class Drag Methods
    // ---------------------------------------
    py::enum_<SPH::DragMethods>(m_sub, "DragMethods")
            .value("None", SPH::DragMethods::None)
            .value("Macklin2014", SPH::DragMethods::Macklin2014)
            .value("Gissler2017", SPH::DragMethods::Gissler2017)
            .value("NumDragMethods", SPH::DragMethods::NumDragMethods);

    // ---------------------------------------
    // Enum class Elasticity Methods
    // ---------------------------------------
    py::enum_<SPH::ElasticityMethods>(m_sub, "ElasticityMethods")
            .value("None", SPH::ElasticityMethods::None)
            .value("Becker2009", SPH::ElasticityMethods::Becker2009)
            .value("Peer2018", SPH::ElasticityMethods::Peer2018)
            .value("NumElasticityMethods", SPH::ElasticityMethods::NumElasticityMethods);

    // ---------------------------------------
    // Enum class Particle State
    // ---------------------------------------
    py::enum_<SPH::ParticleState>(m_sub, "ParticleState")
            .value("Active", SPH::ParticleState::Active)
            .value("AnimatedByEmitter", SPH::ParticleState::AnimatedByEmitter);

}
