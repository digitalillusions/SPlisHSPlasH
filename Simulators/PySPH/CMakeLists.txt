cmake_minimum_required(VERSION 3.2)

project(PySPlisHSPlasH)

set(SIMULATION_LINK_LIBRARIES AntTweakBar glew SPlisHSPlasH Utilities partio zlib MD5 tinyexpr)
set(SIMULATION_DEPENDENCIES AntTweakBar glew SPlisHSPlasH Utilities partio zlib MD5 tinyexpr)

if(WIN32)
  set(SIMULATION_LINK_LIBRARIES freeglut opengl32.lib glu32.lib ${SIMULATION_LINK_LIBRARIES})
  set(SIMULATION_DEPENDENCIES freeglut ${SIMULATION_DEPENDENCIES})
else()
  set(OpenGL_GL_PREFERENCE GLVND)
  find_package(GLUT REQUIRED)
  find_package(OpenGL REQUIRED)

  include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

  set(SIMULATION_LINK_LIBRARIES
	${SIMULATION_LINK_LIBRARIES}
	${GLUT_LIBRARIES}
	${OPENGL_LIBRARIES}
  )
endif()

find_package( Eigen3 REQUIRED )
include_directories( ${EIGEN3_INCLUDE_DIR} )

############################################################
# NeighborhoodSearch
############################################################
include_directories(${NEIGHBORHOOD_SEARCH_INCLUDE_DIR})
set(SIMULATION_DEPENDENCIES ${SIMULATION_DEPENDENCIES} Ext_NeighborhoodSearch)
set(SIMULATION_LINK_LIBRARIES ${SIMULATION_LINK_LIBRARIES} ${NEIGHBORHOOD_SEARCH_LIBRARIES})

############################################################
# DiscreGrid
############################################################
include_directories(${PROJECT_PATH}/extern/install/Discregrid/include)
set(SIMULATION_DEPENDENCIES ${SIMULATION_DEPENDENCIES} Ext_Discregrid)
set(SIMULATION_LINK_LIBRARIES ${SIMULATION_LINK_LIBRARIES}
	optimized Discregrid
	debug Discregrid_d)
link_directories(${PROJECT_PATH}/extern/install/Discregrid/lib)

############################################################
# GenericParameters
############################################################
include_directories(${PROJECT_PATH}/extern/install/GenericParameters/include)
set(SIMULATION_DEPENDENCIES ${SIMULATION_DEPENDENCIES} Ext_GenericParameters)

add_subdirectory(pybind11)

pybind11_add_module(PySPH 
  main.cpp 
  SPHKernelsModule.cpp
  AnimationFieldModule.cpp
  ${VIS_FILES})

if(DL_OUTPUT)
	add_definitions(-DDL_OUTPUT)
endif()
add_definitions(-DTW_NO_LIB_PRAGMA -DTW_STATIC)

include_directories(${PROJECT_PATH}/extern/freeglut/include)
include_directories(${PROJECT_PATH}/extern/glew/include)

# target_link_libraries(PySPH PRIVATE SPlisHSPlasH Utilities Ext_NeighborhoodSearch Ext_Discregrid)
add_dependencies(PySPH ${SIMULATION_DEPENDENCIES})
target_link_libraries(PySPH PRIVATE ${SIMULATION_LINK_LIBRARIES})