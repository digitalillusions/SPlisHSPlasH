#include <pybind11/pybind11.h>

// Put this here for now
#include <SPlisHSPlasH/Common.h>
#include <Utilities/Logger.h>
#include <Utilities/Timing.h>
#include <Utilities/Counting.h>
INIT_LOGGING
INIT_TIMING
INIT_COUNTING
// TODO: Move this to simulator base class

namespace py = pybind11;

void AnimationFieldModule(py::module);
void CommonModule(py::module);
void BoundaryModelModule(py::module);
void EmitterModule(py::module);
void FluidModelModule(py::module);
void UtilitiesModule(py::module);
void SimulationModule(py::module);
void SPHKernelsModule(py::module);

PYBIND11_MODULE(PySPH, m){
    CommonModule(m);
	SPHKernelsModule(m);
	AnimationFieldModule(m);
	UtilitiesModule(m);
	BoundaryModelModule(m);
	EmitterModule(m);
	FluidModelModule(m);
	SimulationModule(m);
}