//
// Created by sjeske on 1/28/20.
//
#include <SPlisHSPlasH/IISPH/SimulationDataIISPH.h>

#include <pybind11/pybind11.h>
#include <SPlisHSPlasH/NonPressureForceBase.h>
#include <SPlisHSPlasH/SurfaceTension/SurfaceTensionBase.h>

namespace py = pybind11;

void SurfaceTensionModule(py::module m_sub) {
    // ---------------------------------------
    // Class Surface Tension Base
    // ---------------------------------------
    py::class_<SPH::SurfaceTensionBase, SPH::NonPressureForceBase>(m_sub, "SurfaceTensionBase")
            .def_readwrite_static("SURFACE_TENSION", &SPH::SurfaceTensionBase::SURFACE_TENSION)
            .def_readwrite_static("SURFACE_TENSION_BOUNDARY", &SPH::SurfaceTensionBase::SURFACE_TENSION_BOUNDARY);
}