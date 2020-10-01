set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin" CACHE INTERNAL "Where to place executables and dlls")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin" CACHE INTERNAL "Where to place executables and dlls in release mode")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_RELWITHDEBINFO_POSTFIX "_rd")
set(CMAKE_MINSIZEREL_POSTFIX "_ms")

include(CMakeDependentOption)

OPTION(USE_DOUBLE_PRECISION "Use double precision"	OFF)
if (USE_DOUBLE_PRECISION)
	add_definitions( -DUSE_DOUBLE)	
	message("AVX is only supported for single precision.")
endif (USE_DOUBLE_PRECISION)

cmake_dependent_option(USE_AVX "Use AVX" ON "NOT USE_DOUBLE_PRECISION" OFF)
if (USE_AVX)
	message(STATUS "If your CPU does not support AVX, turn off the USE_AVX flag.")
	add_definitions(-DUSE_AVX)
endif()

cmake_dependent_option(USE_PERFORMANCE_OPTIMIZATION "Optimize performance (higher memory consumption)" ON "USE_AVX" OFF)
if (USE_PERFORMANCE_OPTIMIZATION)
	add_definitions( -DUSE_PERFORMANCE_OPTIMIZATION)	
endif (USE_PERFORMANCE_OPTIMIZATION)


find_package(Python COMPONENTS Interpreter QUIET)
cmake_dependent_option(USE_PYTHON_BINDINGS "Generate Python Bindings using PyBind11" ON "Python_FOUND OR PYTHON_EXECUTABLE" OFF)
if (USE_PYTHON_BINDINGS AND UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    message(STATUS "Adding -fPIC option when generating Python bindings using GCC")
endif ()

option(CI_BUILD "Build on CI System" OFF)
mark_as_advanced(CI_BUILD)

if (NOT WIN32)
	if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
	  if (NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
	  endif()
	endif()
endif()

option(USE_OpenMP "Use OpenMP" ON)
if(USE_OpenMP)
	option(APPLE_OMP_AUTOADD "Add OpenMP if using AppleClang" ON)

	find_package(OpenMP QUIET)
	if(NOT "${OpenMP_FOUND}" OR NOT "${OpenMP_CXX_FOUND}")
		if("${APPLE_OMP_AUTOADD}" AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7")
			message(STATUS "AppleClang >= 7.0 detected, adding OpenMP. Disable with -DAPPLE_OMP_AUTOADD=OFF")

			find_program(BREW NAMES brew)
			if(BREW)
				execute_process(COMMAND ${BREW} ls libomp RESULT_VARIABLE BREW_RESULT_CODE OUTPUT_QUIET ERROR_QUIET)
				if(BREW_RESULT_CODE)
					message(STATUS "This program supports OpenMP on Mac through Brew. Please run \"brew install libomp\"")
				else()
					execute_process(COMMAND ${BREW} --prefix libomp OUTPUT_VARIABLE BREW_LIBOMP_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)
					set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
					set(OpenMP_CXX_LIB_NAMES "omp")
					set(OpenMP_omp_LIBRARY "${BREW_LIBOMP_PREFIX}/lib/libomp.dylib")
					set(OpenMP_INCLUDE_DIR "${BREW_LIBOMP_PREFIX}/include")
					include_directories("${BREW_LIBOMP_PREFIX}/include")
					message(STATUS "Using Homebrew libomp from ${BREW_LIBOMP_PREFIX}")
				endif()
			else()
				message(STATUS "This program supports OpenMP on Mac through Homebrew, installing Homebrew recommmended https://brew.sh")
			endif()
		endif()
	endif()
	if(OPENMP_FOUND)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	endif()
endif()

if (MSVC)
    set(CMAKE_USE_RELATIVE_PATHS "1")
    # Set compiler flags for "release"
    set(CMAKE_CXX_FLAGS_RELEASE "/MD /MP /Ox /Ob2 /Oi /Ot /fp:fast /D NDEBUG") 
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /MP /Ox /Ob2 /Oi /Ot /fp:fast /D NDEBUG") 
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP") 
	if (USE_AVX)
		add_compile_options("/arch:AVX")
	endif()
endif (MSVC)

if (UNIX OR MINGW)
    set(CMAKE_USE_RELATIVE_PATHS "1")
    # Set compiler flags for "release" Use generic 64 bit instructions when building on CI
	if (CI_BUILD)
		set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=x86-64")
		set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -DNDEBUG -march=x86-64")
	else()
		set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
		set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -DNDEBUG -march=native")
	endif ()
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
	if (USE_AVX)
		add_compile_options("-mavx")
	endif()
endif (UNIX OR MINGW)
if(MINGW)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1 -Wa,-mbig-obj")
endif(MINGW)

if(APPLE)
	set(CMAKE_MACOSX_RPATH 1)
endif()

if (MSVC)
add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif(MSVC)

set(CMAKE_CXX_STANDARD 11)
