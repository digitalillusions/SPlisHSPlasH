//
// Created by sjeske on 1/22/20.
//
#include <SPlisHSPlasH/Simulation.h>
#include <SPlisHSPlasH/TimeStep.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;

void SimulationModule(py::module m_sub){
    // ---------------------------------------
    // Enum Simulation Methods
    // ---------------------------------------
    py::enum_<SPH::SimulationMethods>(m_sub, "SimulationMethods")
            .value("WCSPH", SPH::SimulationMethods::WCSPH)
            .value("PCISPH", SPH::SimulationMethods::PCISPH)
            .value("PBF", SPH::SimulationMethods::PBF)
            .value("IISPH", SPH::SimulationMethods::IISPH)
            .value("DFSPH", SPH::SimulationMethods::DFSPH)
            .value("PF", SPH::SimulationMethods::PF)
            .value("NumSimulationMethods", SPH::SimulationMethods::NumSimulationMethods);

    // ---------------------------------------
    // Enum Boundary Handling Methods
    // ---------------------------------------
    py::enum_<SPH::BoundaryHandlingMethods>(m_sub, "BoundaryHandlingMethods")
            .value("Akinci2012", SPH::BoundaryHandlingMethods::Akinci2012)
            .value("Koschier2017", SPH::BoundaryHandlingMethods::Koschier2017)
            .value("Bender2019", SPH::BoundaryHandlingMethods::Bender2019)
            .value("NumSimulationMethods", SPH::BoundaryHandlingMethods::NumSimulationMethods);

    // ---------------------------------------
    // Class Simulation
    // ---------------------------------------
    py::class_<SPH::Simulation>(m_sub, "Simulation")
            .def_readwrite_static("SIM2D", &SPH::Simulation::SIM_2D)
            .def_readwrite_static("PARTICLE_RADIUS", &SPH::Simulation::PARTICLE_RADIUS)
            .def_readwrite_static("GRAVITATION", &SPH::Simulation::GRAVITATION)
            .def_readwrite_static("CFL_METHOD", &SPH::Simulation::CFL_METHOD)
            .def_readwrite_static("CFL_FACTOR", &SPH::Simulation::CFL_FACTOR)
            .def_readwrite_static("CFL_MAX_TIMESTEPSIZE", &SPH::Simulation::CFL_MAX_TIMESTEPSIZE)
            .def_readwrite_static("ENABLE_Z_SORT", &SPH::Simulation::ENABLE_Z_SORT)

            .def_readwrite_static("KERNEL_METHOD", &SPH::Simulation::KERNEL_METHOD)
            .def_readwrite_static("GRAD_KERNEL_METHOD", &SPH::Simulation::GRAD_KERNEL_METHOD)
            .def_readwrite_static("ENUM_KERNEL_CUBIC", &SPH::Simulation::ENUM_KERNEL_CUBIC)
            .def_readwrite_static("ENUM_KERNEL_WENDLANDQUINTICC2", &SPH::Simulation::ENUM_KERNEL_WENDLANDQUINTICC2)
            .def_readwrite_static("ENUM_KERNEL_POLY6", &SPH::Simulation::ENUM_KERNEL_POLY6)
            .def_readwrite_static("ENUM_KERNEL_SPIKY", &SPH::Simulation::ENUM_KERNEL_SPIKY)
            .def_readwrite_static("ENUM_KERNEL_PRECOMPUTED_CUBIC", &SPH::Simulation::ENUM_KERNEL_PRECOMPUTED_CUBIC)
            .def_readwrite_static("ENUM_KERNEL_CUBIC_2D", &SPH::Simulation::ENUM_KERNEL_CUBIC_2D)
            .def_readwrite_static("ENUM_KERNEL_WENDLANDQUINTICC2_2D", &SPH::Simulation::ENUM_KERNEL_WENDLANDQUINTICC2_2D)
            .def_readwrite_static("ENUM_GRADKERNEL_CUBIC", &SPH::Simulation::ENUM_GRADKERNEL_CUBIC)
            .def_readwrite_static("ENUM_GRADKERNEL_WENDLANDQUINTICC2", &SPH::Simulation::ENUM_GRADKERNEL_WENDLANDQUINTICC2)
            .def_readwrite_static("ENUM_GRADKERNEL_POLY6", &SPH::Simulation::ENUM_GRADKERNEL_POLY6)
            .def_readwrite_static("ENUM_GRADKERNEL_SPIKY", &SPH::Simulation::ENUM_GRADKERNEL_SPIKY)
            .def_readwrite_static("ENUM_GRADKERNEL_PRECOMPUTED_CUBIC", &SPH::Simulation::ENUM_GRADKERNEL_PRECOMPUTED_CUBIC)
            .def_readwrite_static("ENUM_GRADKERNEL_CUBIC_2D", &SPH::Simulation::ENUM_GRADKERNEL_CUBIC_2D)
            .def_readwrite_static("ENUM_GRADKERNEL_WENDLANDQUINTICC2_2D", &SPH::Simulation::ENUM_GRADKERNEL_WENDLANDQUINTICC2_2D)

            .def_readwrite_static("SIMULATION_METHOD", &SPH::Simulation::SIMULATION_METHOD)

            .def_readwrite_static("ENUM_CFL_NONE", &SPH::Simulation::ENUM_CFL_NONE)
            .def_readwrite_static("ENUM_CFL_STANDARD", &SPH::Simulation::ENUM_CFL_STANDARD)
            .def_readwrite_static("ENUM_CFL_ITER", &SPH::Simulation::ENUM_CFL_ITER)

            .def_readwrite_static("ENUM_SIMULATION_WCSPH", &SPH::Simulation::ENUM_SIMULATION_WCSPH)
            .def_readwrite_static("ENUM_SIMULATION_PCISPH", &SPH::Simulation::ENUM_SIMULATION_PCISPH)
            .def_readwrite_static("ENUM_SIMULATION_PBF", &SPH::Simulation::ENUM_SIMULATION_PBF)
            .def_readwrite_static("ENUM_SIMULATION_IISPH", &SPH::Simulation::ENUM_SIMULATION_IISPH)
            .def_readwrite_static("ENUM_SIMULATION_DFSPH", &SPH::Simulation::ENUM_SIMULATION_DFSPH)
            .def_readwrite_static("ENUM_SIMULATION_PF", &SPH::Simulation::ENUM_SIMULATION_PF)

            .def_readwrite_static("BOUNDARY_HANDLING_METHOD", &SPH::Simulation::BOUNDARY_HANDLING_METHOD)
            .def_readwrite_static("ENUM_AKINCI2012", &SPH::Simulation::ENUM_AKINCI2012)
            .def_readwrite_static("ENUM_KOSCHIER2017", &SPH::Simulation::ENUM_KOSCHIER2017)
            .def_readwrite_static("ENUM_BENDER2019", &SPH::Simulation::ENUM_BENDER2019)

            .def(py::init<>())
            .def("init", &SPH::Simulation::init)
            .def("reset", &SPH::Simulation::reset)
            .def_static("getCurrent", &SPH::Simulation::getCurrent, py::return_value_policy::reference_internal)
            .def_static("setCurrent", &SPH::Simulation::setCurrent)
            .def_static("hasCurrent", &SPH::Simulation::hasCurrent)

            .def("addFluidModel", &SPH::Simulation::addFluidModel)
            .def("getFluidModel", &SPH::Simulation::getFluidModel, py::return_value_policy::reference_internal)
            .def("getFluidModelFromPointSet", &SPH::Simulation::getFluidModelFromPointSet, py::return_value_policy::reference_internal)
            .def("numberOfFluidModels", &SPH::Simulation::numberOfFluidModels)

            .def("addBoundaryModel", &SPH::Simulation::addBoundaryModel)
            .def("getBoundaryModel", &SPH::Simulation::getBoundaryModel, py::return_value_policy::reference_internal)
            .def("getBoundaryModelFromPointSet", &SPH::Simulation::getBoundaryModelFromPointSet, py::return_value_policy::reference_internal)
            .def("numberOfBoundaryModels", &SPH::Simulation::numberOfBoundaryModels)
            .def("updateBoundaryVolume", &SPH::Simulation::updateBoundaryVolume)

            .def("getAnimationFieldSystem", &SPH::Simulation::getAnimationFieldSystem, py::return_value_policy::reference_internal)

            .def("getBoundaryHandlingMethod", &SPH::Simulation::getBoundaryHandlingMethod)
            .def("setBoundaryHandlingMethod", &SPH::Simulation::setBoundaryHandlingMethod)

            .def("getKernel", &SPH::Simulation::getKernel)
            .def("setKernel", &SPH::Simulation::setKernel)
            .def("getGradKernel", &SPH::Simulation::getGradKernel)
            .def("setGradKernel", &SPH::Simulation::setGradKernel)

            .def("W_zero", &SPH::Simulation::W_zero)
            .def("W", &SPH::Simulation::W)
            .def("gradW", &SPH::Simulation::gradW)

            .def("getSimulationMethod", &SPH::Simulation::getSimulationMethod)
            .def("setSimulationMethod", &SPH::Simulation::setSimulationMethod)
            .def("setSimulationMethodChangedCallback", &SPH::Simulation::setSimulationMethodChangedCallback)
            .def("getTimeStep", &SPH::Simulation::getTimeStep, py::return_value_policy::reference_internal)
            .def("is2DSimulation", &SPH::Simulation::is2DSimulation)
            .def("zSortEnabled", &SPH::Simulation::zSortEnabled)
            .def("setParticleRadius", &SPH::Simulation::setParticleRadius)
            .def("getParticleRadius", &SPH::Simulation::getParticleRadius)
            .def("getSupportRadius", &SPH::Simulation::getSupportRadius)
            .def("updateTimeStepSize", &SPH::Simulation::updateTimeStepSize)
            .def("updateTimeStepSizeCFL", &SPH::Simulation::updateTimeStepSizeCFL)
            .def("performNeighborhoodSearch", &SPH::Simulation::performNeighborhoodSearch)
            .def("performNeighborhoodSearchSort", &SPH::Simulation::performNeighborhoodSearchSort)
            .def("computeNonPressureForces", &SPH::Simulation::computeNonPressureForces)
            .def("animateParticles", &SPH::Simulation::animateParticles)
            .def("emitParticles", &SPH::Simulation::emitParticles)
            .def("emittedParticles", &SPH::Simulation::emittedParticles)
            .def("getNeighborhoodSearch", &SPH::Simulation::getNeighborhoodSearch, py::return_value_policy::reference_internal)
            .def("saveState", &SPH::Simulation::saveState)
            .def("loadState", &SPH::Simulation::loadState)
            .def("numberOfPointSets", &SPH::Simulation::numberOfPointSets)
            .def("numberOfNeighbors", &SPH::Simulation::numberOfNeighbors)
            .def("getNeighbor", &SPH::Simulation::getNeighbor)
            .def("getNeighborList", &SPH::Simulation::getNeighborList);

}

