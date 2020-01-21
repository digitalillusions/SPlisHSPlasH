#include <SPlisHSPlasH/Common.h>
#include <SPlisHSPlasH/AnimationField.h>
#include <SPlisHSPlasH/AnimationFieldSystem.h>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>


namespace py = pybind11;

void AnimationFieldModule(py::module m) {
	py::class_<SPH::AnimationField>(m, "AnimationField")
		.def(py::init<>([](
			const std::string &particleFieldName,
			const Vector3r &pos, const Matrix3r & rotation, const Vector3r &scale,
			const std::string expression[3], const unsigned int type = 0) {
				return SPH::AnimationField(particleFieldName, pos, rotation, scale, expression, type); }))
		.def("setStartTime", &SPH::AnimationField::setStartTime)
		.def("setEndTime", &SPH::AnimationField::setEndTime)
		.def("step", &SPH::AnimationField::step);

	py::class_<SPH::AnimationFieldSystem>(m, "AnimationFieldSystem")
		.def(py::init<>())
		.def("addAnimationField", &SPH::AnimationFieldSystem::addAnimationField)
		.def("numAnimationFields", &SPH::AnimationFieldSystem::numAnimationFields)
		.def("getAnimationFields", &SPH::AnimationFieldSystem::getAnimationFields)
		.def("step", &SPH::AnimationFieldSystem::step)
		.def("reset", &SPH::AnimationFieldSystem::reset);
}