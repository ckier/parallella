cmake_minimum_required(VERSION 3.0)
project(VectorMultiply)

add_definitions(-v -std=c++11)

set(SOURCE_FILES hello-opencl.cpp)

if (CONFIG_ARCH STREQUAL amd64)
    add_definitions(-DDEVICE_TYPE=CL_DEVICE_TYPE_CPU)
    add_definitions(-DREQUESTED_NUMBER_DEVICES=5)
    set(OPENCL_LIB OpenCL)
endif ()

if (CONFIG_ARCH STREQUAL arm)
    add_definitions(-DDEVICE_TYPE=CL_DEVICE_TYPE_ACCELERATOR)
    add_definitions(-DREQUESTED_NUMBER_DEVICES=0)
    set(OPENCL_LIB libcoprthr_opencl.so)
endif ()

add_executable(para_run_vector ${SOURCE_FILES})
target_link_libraries(para_run_vector ${OPENCL_LIB})
