# How to compile the splishsplash library on MacOS
## Useful links
* [Something about getting OpenMP to run on MacOS](https://iscinumpy.gitlab.io/post/omp-on-high-sierra/)

## Getting CompactNSearch to work
First problem was, that the `ppl.h` file that is used on Windows for the function `Concurrency::parallel_for_each` does not exist on MacOS.
Instead I used a workaround from [here](https://xenakios.wordpress.com/2014/09/29/concurrency-in-c-the-cross-platform-way/) which is also
implemented in this [commit](https://github.com/zelmon64/PSMoveService/commit/476805b7ba323c4a4bbe3e7fe4050e2369c7b180). Using this I added
compiler flags specific to Apple in order to define the function should it be necessary in `config.h`
```c++
#ifdef _MSC_VER
	#include <ppl.h>
#elif __APPLE__
	#include "dispatch/dispatch.h"
#else
	#include <parallel/algorithm>
#endif
```
and in `CompactNSearch.cpp` and `main.cpp`
```c++
#ifdef __APPLE__
template<typename It, typename F>
inline void parallel_for_each(It a, It b, F&& f)
{
        size_t count = std::distance(a, b);
        using data_t = std::pair<It, F>;
        data_t helper = data_t(a, std::forward<F>(f));
        dispatch_apply_f(count, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), &helper, [](void* ctx, size_t cnt)
        {
                data_t* d = static_cast<data_t*>(ctx);
                auto elem_it = std::next(d->first, cnt);
                (*d).second(*(elem_it));
        });
}
#endif
```
```c++
#ifdef _MSC_VER
	concurrency::parallel_for_each
#elif __APPLE__
	parallel_for_each
#else
	__gnu_parallel::for_each
#endif
```
Further investigation is needed if this actually works during runtime. However, this does compile without a problem.

## Discregrid
Discregrid is also required by SplishSplash. This library uses OpenMP which was not made optional. I will now try to make OpenMP work on MacOS first using simple examples. Used the first link above to add the following code to the `CMakeLists.txt`
```cmake
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
INCLUDE(PatchOpenMPApple)
#ADD_DEFINITIONS(${OpenMP_CXX_FLAGS})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
TARGET_LINK_LIBRARIES(OMP_TEST ${OpenMP_omp_LIBRARY})
```
then in the `${PROJECT_SOURCE_DIR}/cmake` directory one has to add a `PatchOpenMPApple.cmake` file with the following code
```cmake
# This file adds OpenMP to your project if you are using Apple Clang.

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
                include_directories("${BREW_LIBOMP_PREFIX}/include")
                message(STATUS "Using Homebrew libomp from ${BREW_LIBOMP_PREFIX}")
            endif()
        else()
            message(STATUS "This program supports OpenMP on Mac through Homebrew, installing Homebrew recommmended https://brew.sh")
        endif()
    endif()
endif()
```
After this, the clang compiler complains about alot of things, that are resolved, as soon as the following line is added to the top level Discregrid `CMakeLists.txt` file.
```cmake
SET(CMAKE_CXX_STANDARD 11)
```
Then an error should occur, where a variable name is used as the name of the same class. This error occurs in `kd_tree.inl` and is resolved by the following code
```c++
{
	auto const& node_ = node(node_index);
	computeHull(node_.begin, node_.n, hull(node_index));
}
```

## In-Between
Had to remove several `include "omp.h"` and omp functions from the code, so that it compiles. 
Edit: This is no longer necessary, it seems to be possible using a combination of the above methods, to be able to include and compile omp functions. 

## Main Project
After getting several linker errors about omp symbols not being found, I decided to add the OpenMP library and preprocessor to the top level `CMakeLists.txt` file.
```cmake
############################################################
# OpenMPApple
############################################################
if(APPLE)
    INCLUDE(PatchOpenMPApple)
    set(CMAKE_VERBOSE_MAKEFILE ON)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
```
*Note that the verbose mode was turned on for debugging the output* Afterwards however, the OpenMP variables remained unset and I kept wondering why. This was because for whatever reason, the compiler that was found on the top level, even though being AppleClang 10.x, was idetifies as `Clang` and not `AppleClang` and therefore not recognised by the `PatchOpenMPApple` script. To fix this the following line was commented in the included script.
```cmake
#if("${APPLE_OMP_AUTOADD}" AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7")
```
Afterwards the `${OpenMP_omp_LIBRARY}` variable had to be added to `SIMULATION_LINK_LIBRARIES` in both the DynamicBoundaryDemo and StaticBoundaryDemo `CMakeLists.txt` file.
```cmake
set(SIMULATION_LINK_LIBRARIES
	${SIMULATION_LINK_LIBRARIES}
	${GLUT_LIBRARIES}
	${OPENGL_LIBRARIES}
	${OpenMP_omp_LIBRARY}
```
in addition the `${GLUT_LIBRARIES}` were redefined to include the freeglut library installed using homebrew. If this actually works in the program remains to be seen. However, it did fix the linker issue of missing symbols. Edit: This indeed works, but only in the reviewed version where the glut libraries were overwritten by `freeglut`.
```cmake
if(APPLE)
	#MESSAGE(STATUS "Glut libs are ${GLUT_LIBRARIES}")
	set(GLUT_LIBRARIES ${GLUT_LIBRARIES} "/usr/local/opt/freeglut/lib/libglut.dylib")
	#set(GLUT_LIBRARIES "/usr/local/opt/freeglut/lib/libglut.dylib")
endif()
```
Now I'm getting a very annoying compiler error and need to go to bed. 
It seems, that this error is fixed by commenting line 60 in `Tools/SurfaceSampling/main.cpp`. For now this seems to be a fine option. 

## Addition notes
In both the `Common.cmake` of the external `Discregrid` as well as of the main `SPlishSPlash` the following things have to be adjusted. 
```cmake
if (UNIX AND NOT APPLE)
    set(CMAKE_USE_RELATIVE_PATHS "1")
    # Set compiler flags for "release"
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -fopenmp") 
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fopenmp") 
endif (UNIX AND NOT APPLE)

if(APPLE)
    set(CMAKE_USE_RELATIVE_PATHS "1")
    # Set compiler flags for "release"
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Xpreprocessor -fopenmp")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Xpreprocessor -fopenmp")
    set(CMAKE_MACOSX_RPATH 1)
endif(APPLE)
```

