//
// Created by sjeske on 1/22/20.
//
#include <vector>
#include <array>
#include <iostream>

#include <Utilities/BinaryFileReaderWriter.h>
#include <Utilities/Counting.h>
#include <Utilities/FileSystem.h>
#include <Utilities/OBJLoader.h>
#include <Utilities/PartioReaderWriter.h>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/chrono.h>

#ifdef PY_NO_CXX14
template <typename... Args>
using overload_cast_ = pybind11::detail::overload_cast_impl<Args...>;
#else
//using overload_cast_ = pybind11::overload_cast;
#endif

PYBIND11_MAKE_OPAQUE(std::vector<std::array<float, 3>>)
PYBIND11_MAKE_OPAQUE(std::vector<std::array<float, 2>>)
PYBIND11_MAKE_OPAQUE(std::vector<Vector3r>)
PYBIND11_MAKE_OPAQUE(std::vector<Utilities::MeshFaceIndices>)

namespace py = pybind11;

void UtilitiesModule(py::module m){
    // Utilities submodule
    auto m_sub = m.def_submodule("Utilities");

    // ---------------------------------------
    // Binary File reader and writer
    // ---------------------------------------
    py::class_<SPH::BinaryFileWriter>(m_sub, "BinaryFileWriter")
            .def(py::init<>())
            .def("openFile", &SPH::BinaryFileWriter::openFile)
            .def("closeFile", &SPH::BinaryFileWriter::closeFile);

    py::class_<SPH::BinaryFileReader>(m_sub, "BinaryFileReader")
            .def(py::init<>())
            .def("openFile", &SPH::BinaryFileReader::openFile)
            .def("closeFile", &SPH::BinaryFileReader::closeFile);

    // ---------------------------------------
    // Counting class
    // ---------------------------------------
    py::class_<Utilities::AverageCount>(m_sub, "AverageCount")
            .def(py::init<>())
            .def_readwrite("sum", &Utilities::AverageCount::sum)
            .def_readwrite("numberOfCalls", &Utilities::AverageCount::numberOfCalls);

    py::class_<Utilities::Counting>(m_sub, "Counting")
            .def(py::init<>())
            .def_readwrite_static("m_averageCounts", &Utilities::Counting::m_averageCounts)
            .def_static("reset", &Utilities::Counting::reset)
            .def_static("increaseCounter", &Utilities::Counting::increaseCounter)
            .def_static("printAverageCounts", &Utilities::Counting::printAverageCounts)
            .def_static("printCounterSums", &Utilities::Counting::printCounterSums);

    // TODO: check if init counting need to be implemented
    m_sub.def("INCREASE_COUNTER", &Utilities::Counting::increaseCounter);

    // ---------------------------------------
    // File System utilities
    // ---------------------------------------
    py::class_<Utilities::FileSystem>(m_sub, "FileSystem")
            .def(py::init<>())
            .def_static("getFilePath", Utilities::FileSystem::getFilePath)
            .def_static("getFileName", Utilities::FileSystem::getFileName)
            .def_static("getFileNameWithExt", Utilities::FileSystem::getFileNameWithExt)
            .def_static("getFileExt", Utilities::FileSystem::getFileExt)
            .def_static("isRelativePath", Utilities::FileSystem::isRelativePath)
            .def_static("makeDir", Utilities::FileSystem::makeDir)
            .def_static("makeDirs", Utilities::FileSystem::makeDirs)
            .def_static("normalizePath", Utilities::FileSystem::normalizePath)
            .def_static("fileExists", Utilities::FileSystem::fileExists)
            .def_static("getProgramPath", Utilities::FileSystem::getProgramPath)
            .def_static("copyFile", Utilities::FileSystem::copyFile)
            .def_static("isFile", Utilities::FileSystem::isFile)
            .def_static("isDirectory", Utilities::FileSystem::isDirectory)
            .def_static("getFilesInDirectory", Utilities::FileSystem::getFilesInDirectory)
            .def_static("getFileMD5", Utilities::FileSystem::getFileMD5)
            .def_static("writeMD5File", Utilities::FileSystem::writeMD5File)
            .def_static("checkMD5", Utilities::FileSystem::checkMD5);

    // ---------------------------------------
    // Logger
    // ---------------------------------------
    py::enum_<Utilities::LogLevel>(m_sub, "LogLevel")
            .value("DEBUG", Utilities::LogLevel::DEBUG)
            .value("INFO", Utilities::LogLevel::INFO)
            .value("WARN", Utilities::LogLevel::WARN)
            .value("ERR", Utilities::LogLevel::ERR)
            .export_values();

    py::class_<Utilities::ConsoleSink>(m_sub, "ConsoleSink")
            .def(py::init<>([](const Utilities::LogLevel minLevel){
                return Utilities::ConsoleSink(minLevel);
            }))
            .def("write", &Utilities::ConsoleSink::write);

    // TODO: check if it is okay to use shared pointer and implement the actual logger functions
    py::class_<Utilities::FileSink, std::shared_ptr<Utilities::FileSink>>(m_sub, "FileSink")
            .def(py::init<>([](const Utilities::LogLevel minLevel, const std::string &fileName){
                return std::make_shared<Utilities::FileSink>(minLevel, fileName);
            }))
            .def("write", &Utilities::FileSink::write);

    // ---------------------------------------
    // Object loader necessary vector types
    // ---------------------------------------
    py::bind_vector<std::vector<std::array<float, 3>>>(m_sub, "VecVec3f");
    py::bind_vector<std::vector<std::array<float, 2>>>(m_sub, "VecVec2f");
    py::bind_vector<std::vector<Utilities::MeshFaceIndices>>(m_sub, "VecMeshFaceIndices");

    // Todo: Bind missing attributes
    py::class_<Utilities::MeshFaceIndices>(m_sub, "MeshFaceIndices")
            .def(py::init<>())
            .def("__repr__", [](const Utilities::MeshFaceIndices &m){
                std::stringstream s;
                s << "posIndices\n" << m.posIndices[0] << " " << m.posIndices[1] << " " << m.posIndices[2] << "\n";
                s << "texIndices\n" << m.texIndices[0] << " " << m.texIndices[1] << " " << m.texIndices[2] << "\n";
                s << "normalIndices\n" << m.normalIndices[0] << " " << m.normalIndices[1] << " " << m.normalIndices[2] << "\n";
                return s.str();
            });

    py::class_<Utilities::OBJLoader>(m_sub, "OBJLoader")
            .def(py::init<>())
            .def_static("loadObj", &Utilities::OBJLoader::loadObj);

    // ---------------------------------------
    // Partio reader and writer
    // ---------------------------------------
    py::bind_vector<std::vector<Vector3r>>(m_sub, "VecVector3r", "std::vector<Vector3r> not to be confused with"
                                                                 "VecVec3f which ist std::vector<std::array<float,3>>");

    py::class_<Utilities::PartioReaderWriter>(m_sub, "PartioReaderWriter")
            .def(py::init<>())
            .def_static("readParticle", overload_cast_<const std::string &, const Vector3r &, const Matrix3r &,
                    const Real, std::vector<Vector3r> &>()(&Utilities::PartioReaderWriter::readParticles))
            .def_static("readParticle", overload_cast_<const std::string &, const Vector3r &, const Matrix3r &,
                    const Real, std::vector<Vector3r> &, std::vector<Vector3r> &>()(&Utilities::PartioReaderWriter::readParticles))
            .def_static("readParticle", overload_cast_<const std::string &, const Vector3r &, const Matrix3r &,
                    const Real, std::vector<Vector3r> &, std::vector<Vector3r> &, Real &>()(&Utilities::PartioReaderWriter::readParticles))
            .def_static("writeParticle", &Utilities::PartioReaderWriter::writeParticles);

    // ---------------------------------------
    // String tools
    // ---------------------------------------
    // TODO: String tools are omitted, because python is basically one big string tool


    // ---------------------------------------
    // System Info
    // ---------------------------------------
    // TODO: System info is also omitted. Will add if explicitly required by other classes

    // ---------------------------------------
    // Timing
    // ---------------------------------------
    // TODO: Timing and find a way for everything to be actually printed
    py::class_<Utilities::TimingHelper>(m_sub, "TimingHelper")
            .def(py::init<>())
            .def_readwrite("start", &Utilities::TimingHelper::start)
            .def_readwrite("name", &Utilities::TimingHelper::name);

    py::class_<Utilities::AverageTime>(m_sub, "AverageTime")
            .def(py::init<>())
            .def_readwrite("totalTime", &Utilities::AverageTime::totalTime)
            .def_readwrite("counter", &Utilities::AverageTime::counter)
            .def_readwrite("name", &Utilities::AverageTime::name);

    py::class_<Utilities::IDFactory>(m_sub, "IDFactory")
            .def(py::init<>())
            .def_static("getId", &Utilities::IDFactory::getId);

    py::class_<Utilities::Timing>(m_sub, "Timing")
            .def(py::init<>())
            .def_readwrite_static("m_dontPrintTimes", &Utilities::Timing::m_dontPrintTimes)
            .def_readwrite_static("m_startCounter", &Utilities::Timing::m_startCounter)
            .def_readwrite_static("m_stopCounter", &Utilities::Timing::m_stopCounter)
            .def_readwrite_static("m_timingStack", &Utilities::Timing::m_timingStack)
            .def_readwrite_static("m_averageTimes", &Utilities::Timing::m_averageTimes)
            .def_static("reset", &Utilities::Timing::reset)
            .def_static("startTiming", &Utilities::Timing::startTiming)
            .def_static("stopTiming", overload_cast_<bool>()(&Utilities::Timing::stopTiming))
            .def_static("stopTiming", overload_cast_<bool, int&>()(&Utilities::Timing::stopTiming))
            .def_static("printAverageTimes", &Utilities::Timing::printAverageTimes)
            .def_static("printTimeSums", &Utilities::Timing::printTimeSums);
}
