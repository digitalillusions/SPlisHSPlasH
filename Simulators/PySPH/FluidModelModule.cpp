//
// Created by sjeske on 1/22/20.
//
#include <SPlisHSPlasH/FluidModel.h>
#include <SPlisHSPlasH/EmitterSystem.h>
#include <SPlisHSPlasH/SurfaceTension/SurfaceTensionBase.h>
#include <SPlisHSPlasH/Viscosity/ViscosityBase.h>
#include <SPlisHSPlasH/Vorticity/VorticityBase.h>
#include <SPlisHSPlasH/Drag/DragBase.h>
#include <SPlisHSPlasH/Elasticity/ElasticityBase.h>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include <string>

namespace py = pybind11;

template <typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;

// TODO: remove reference getters

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

	// ---------------------------------------
	// Class Fluid Model
	// ---------------------------------------
	py::class_<SPH::FluidModel>(m_sub, "FluidModel")
		.def_readwrite_static("NUM_PARTICLES", &SPH::FluidModel::NUM_PARTICLES)
		.def_readwrite_static("NUM_REUSED_PARTICLES", &SPH::FluidModel::NUM_REUSED_PARTICLES)
		.def_readwrite_static("DENSITY0", &SPH::FluidModel::DENSITY0)

		.def_readwrite_static("DRAG_METHOD", &SPH::FluidModel::DRAG_METHOD)
		.def_readwrite_static("SURFACE_TENSION_METHOD", &SPH::FluidModel::SURFACE_TENSION_METHOD)
		.def_readwrite_static("VISCOSITY_METHOD", &SPH::FluidModel::VISCOSITY_METHOD)
		.def_readwrite_static("VORTICITY_METHOD", &SPH::FluidModel::VORTICITY_METHOD)
		.def_readwrite_static("ELASTICITY_METHOD", &SPH::FluidModel::ELASTICITY_METHOD)

		.def_readwrite_static("ENUM_DRAG_NONE", &SPH::FluidModel::ENUM_DRAG_NONE)
		.def_readwrite_static("ENUM_DRAG_MACKLIN2014", &SPH::FluidModel::ENUM_DRAG_MACKLIN2014)
		.def_readwrite_static("ENUM_DRAG_GISSLER2017", &SPH::FluidModel::ENUM_DRAG_GISSLER2017)

		.def_readwrite_static("ENUM_SURFACETENSION_NONE", &SPH::FluidModel::ENUM_SURFACETENSION_NONE)
		.def_readwrite_static("ENUM_SURFACETENSION_BECKER2007", &SPH::FluidModel::ENUM_SURFACETENSION_BECKER2007)
		.def_readwrite_static("ENUM_SURFACETENSION_AKINCI2013", &SPH::FluidModel::ENUM_SURFACETENSION_AKINCI2013)

		.def_readwrite_static("ENUM_VISCOSITY_NONE", &SPH::FluidModel::ENUM_VISCOSITY_NONE)
		.def_readwrite_static("ENUM_VISCOSITY_STANDARD", &SPH::FluidModel::ENUM_VISCOSITY_STANDARD)
		.def_readwrite_static("ENUM_VISCOSITY_XSPH", &SPH::FluidModel::ENUM_VISCOSITY_XSPH)
		.def_readwrite_static("ENUM_VISCOSITY_BENDER2017", &SPH::FluidModel::ENUM_VISCOSITY_BENDER2017)
		.def_readwrite_static("ENUM_VISCOSITY_PEER2015", &SPH::FluidModel::ENUM_VISCOSITY_PEER2015)
		.def_readwrite_static("ENUM_VISCOSITY_PEER2016", &SPH::FluidModel::ENUM_VISCOSITY_PEER2016)
		.def_readwrite_static("ENUM_VISCOSITY_TAKAHASHI2015", &SPH::FluidModel::ENUM_VISCOSITY_TAKAHASHI2015)
		.def_readwrite_static("ENUM_VISCOSITY_WEILER2018", &SPH::FluidModel::ENUM_VISCOSITY_WEILER2018)

		.def_readwrite_static("ENUM_VORTICITY_NONE", &SPH::FluidModel::ENUM_VORTICITY_NONE)
		.def_readwrite_static("ENUM_VORTICITY_MICROPOLAR", &SPH::FluidModel::ENUM_VORTICITY_MICROPOLAR)
		.def_readwrite_static("ENUM_VORTICITY_VC", &SPH::FluidModel::ENUM_VORTICITY_VC)

		.def_readwrite_static("ENUM_ELASTICITY_NONE", &SPH::FluidModel::ENUM_ELASTICITY_NONE)
		.def_readwrite_static("ENUM_ELASTICITY_BECKER2009", &SPH::FluidModel::ENUM_ELASTICITY_BECKER2009)
		.def_readwrite_static("ENUM_ELASTICITY_PEER2018", &SPH::FluidModel::ENUM_ELASTICITY_PEER2018)

		.def(py::init<>())
		.def("init", &SPH::FluidModel::init)
		.def("getId", &SPH::FluidModel::getId)
		.def("getDensity0", &SPH::FluidModel::getDensity0)
		.def("setDensity0", &SPH::FluidModel::setDensity0)
		.def("getPointSetIndex", &SPH::FluidModel::getPointSetIndex)
		.def("addField", &SPH::FluidModel::addField)
		.def("getFields", &SPH::FluidModel::getFields) // TODO: Bind return vector?
		.def("getField", overload_cast_<const unsigned int>()(&SPH::FluidModel::getField))
		.def("getField", overload_cast_<const std::string&>()(&SPH::FluidModel::getField))
		.def("numberOfFields", &SPH::FluidModel::numberOfFields)
		.def("removeFieldByName", &SPH::FluidModel::removeFieldByName)
		.def("setNumActiveParticles", &SPH::FluidModel::setNumActiveParticles)
		.def("numberOfParticles", &SPH::FluidModel::numberOfParticles)
		.def("getEmitterSystem", &SPH::FluidModel::getEmitterSystem)
		.def("reset", &SPH::FluidModel::reset)
		.def("performNeighborhoodSearchSort", &SPH::FluidModel::performNeighborhoodSearchSort)
		.def("initModel", &SPH::FluidModel::initModel)
		.def("numParticles", &SPH::FluidModel::numParticles)
		.def("numActiveParticles", &SPH::FluidModel::numActiveParticles)
		.def("getNumActiveParticles0", &SPH::FluidModel::getNumActiveParticles0)
		.def("setNumActiveParticles0", &SPH::FluidModel::setNumActiveParticles0)
		.def("emittedParticles", &SPH::FluidModel::emittedParticles)

		.def("getSurfaceTensionMethod", &SPH::FluidModel::getSurfaceTensionMethod)
		.def("setSurfaceTensionMethod", &SPH::FluidModel::setSurfaceTensionMethod)
		.def("getViscosityMethod", &SPH::FluidModel::getViscosityMethod)
		.def("setViscosityMethod", &SPH::FluidModel::setViscosityMethod)
		.def("getVorticityMethod", &SPH::FluidModel::getVorticityMethod)
		.def("setVorticityMethod", &SPH::FluidModel::setVorticityMethod)
		.def("getDragMethod", &SPH::FluidModel::getDragMethod)
		.def("setDragMethod", &SPH::FluidModel::setDragMethod)
		.def("getElasticityMethod", &SPH::FluidModel::getElasticityMethod)
		.def("setElasticityMethod", &SPH::FluidModel::setElasticityMethod)
		.def("setElasticityMethod", &SPH::FluidModel::setElasticityMethod)

		.def("getSurfaceTensionBase", &SPH::FluidModel::getSurfaceTensionBase)
		.def("getViscosityBase", &SPH::FluidModel::getViscosityBase)
		.def("getVorticityBase", &SPH::FluidModel::getVorticityBase)
		.def("getDragBase", &SPH::FluidModel::getDragBase)
		.def("getElasticityBase", &SPH::FluidModel::getElasticityBase)

		.def("setDragMethodChangedCallback", &SPH::FluidModel::setDragMethodChangedCallback)
		.def("setSurfaceMethodChangedCallback", &SPH::FluidModel::setSurfaceMethodChangedCallback)
		.def("setViscosityMethodChangedCallback", &SPH::FluidModel::setViscosityMethodChangedCallback)
		.def("setVorticityMethodChangedCallback", &SPH::FluidModel::setVorticityMethodChangedCallback)
		.def("setElasticityMethodChangedCallback", &SPH::FluidModel::setElasticityMethodChangedCallback)

		.def("computeSurfaceTension", &SPH::FluidModel::computeSurfaceTension)
		.def("computeViscosity", &SPH::FluidModel::computeViscosity)
		.def("computeVorticity", &SPH::FluidModel::computeVorticity)
		.def("computeDragForce", &SPH::FluidModel::computeDragForce)
		.def("computeElasticity", &SPH::FluidModel::computeElasticity)

		.def("saveState", &SPH::FluidModel::saveState)
		.def("loadState", &SPH::FluidModel::loadState)

		.def("getPosition0", (Vector3r& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getPosition0))
		.def("getPosition0", (const Vector3r& (SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getPosition0))
		.def("setPosition0", &SPH::FluidModel::setPosition0)

		.def("getPosition", (Vector3r& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getPosition))
		.def("getPosition", (const Vector3r& (SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getPosition))
		.def("setPosition", &SPH::FluidModel::setPosition)

		.def("getVelocity", (Vector3r& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getVelocity))
		.def("getVelocity", (const Vector3r& (SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getVelocity))
		.def("setVelocity", &SPH::FluidModel::setVelocity)

		.def("getVelocity0", (Vector3r& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getVelocity0))
		.def("getVelocity0", (const Vector3r& (SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getVelocity0))
		.def("setVelocity0", &SPH::FluidModel::setVelocity0)

		.def("getAcceleration", (Vector3r& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getAcceleration))
		.def("getAcceleration", (const Vector3r& (SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getAcceleration))
		.def("setAcceleration", &SPH::FluidModel::setAcceleration)

		.def("getMass", (Real& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getMass))
		.def("getMass", (const Real& (SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getMass))
		.def("setMass", &SPH::FluidModel::setMass)

		.def("getDensity", (Real& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getDensity))
		.def("getDensity", (const Real&(SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getDensity))
		.def("setMass", &SPH::FluidModel::setMass)

		.def("getParticleId", (unsigned int& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getParticleId))
		.def("getParticleId", (const unsigned int&(SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getParticleId))

		.def("getParticleState", (SPH::ParticleState& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getParticleState))
		.def("getParticleState", (const SPH::ParticleState&(SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getParticleState))
		.def("setParticleState", &SPH::FluidModel::setParticleState)

		.def("getVolume", (Real& (SPH::FluidModel::*)(const unsigned int))(&SPH::FluidModel::getVolume))
		.def("getVolume", (const Real& (SPH::FluidModel::*)(const unsigned int)const)(&SPH::FluidModel::getVolume));
}
