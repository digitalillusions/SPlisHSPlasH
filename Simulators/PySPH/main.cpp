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

void CommonModule(py::module m);
void SPHKernelsModule(py::module m);
void AnimationFieldModule(py::module m);
void UtilitiesModule(py::module m);

PYBIND11_MODULE(PySPH, m){
    CommonModule(m);
	SPHKernelsModule(m);
	AnimationFieldModule(m);
	UtilitiesModule(m);
}