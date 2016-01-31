cmake_minimum_required(VERSION 3.0)
project(ExploreOpenCL)

add_definitions(-v -std=c++11)

set(HEADER_FILES AcceleratorDevice.h Utilities.h)
set(SOURCE_FILES AcceleratorDevice.cpp Utilities.cpp)

if (CONFIG_ARCH STREQUAL amd64)
    add_definitions(-DDEVICE_TYPE=CL_DEVICE_TYPE_ALL)
    add_definitions(-DREQUESTED_NUMBER_DEVICES=5)
    set(OPENCL_LIB OpenCL)
endif ()

if (CONFIG_ARCH STREQUAL arm)
    add_definitions(-DDEVICE_TYPE=CL_DEVICE_TYPE_ACCELERATOR)
    add_definitions(-DREQUESTED_NUMBER_DEVICES=0)
    set(OPENCL_LIB libcoprthr_opencl.so)
endif ()

add_library(ExploreOpenCL STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(ExploreOpenCL ${OPENCL_LIB} log4cpp)
