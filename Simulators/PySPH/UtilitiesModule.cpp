//
// Created by sjeske on 1/22/20.
//

#include <Utilities/BinaryFileReaderWriter.h>
#include <Utilities/Counting.h>
#include <Utilities/FileSystem.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void UtilitiesModule(py::module m){
    // Utilities submodule
    auto m_sub = m.def_submodule("Utilities");

    // Binary File reader and writer
    py::class_<SPH::BinaryFileWriter>(m_sub, "BinaryFileWriter")
            .def(py::init<>())
            .def("openFile", &SPH::BinaryFileWriter::openFile)
            .def("closeFile", &SPH::BinaryFileWriter::closeFile);

    py::class_<SPH::BinaryFileReader>(m_sub, "BinaryFileReader")
            .def(py::init<>())
            .def("openFile", &SPH::BinaryFileReader::openFile)
            .def("closeFile", &SPH::BinaryFileReader::closeFile);

    // Counting class TODO: check if init counting need to be implemented
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

    m_sub.def("INCREASE_COUNTER", &Utilities::Counting::increaseCounter);

    // File System utilities
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

    // Logger
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


}
