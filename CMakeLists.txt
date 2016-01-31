cmake_minimum_required(VERSION 3.0)
project(Parallella)

# Set to ON to make debug output active, Off otherwise.
set(DEBUG ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Arch must be set to amd64 or arm.
#set(CONFIG_ARCH arm)
set(CONFIG_ARCH amd64)

if (NOT ${CONFIG_ARCH} MATCHES "amd64|arm")
    message(FATAL_ERROR "Architecture not supported: ${CONFIG_ARCH}")
endif ()

# Config must be set to Debug or Release.
if (NOT ${CMAKE_BUILD_TYPE} MATCHES "Debug|Release|RelWithDebInfo|MinSizeRel")
    message(FATAL_ERROR "Configuration not supported: ${CMAKE_BUILD_TYPE}")
endif ()

add_definitions(-v -std=c++11)

if (CONFIG_ARCH STREQUAL arm)
    # Set environment to cross compile to arm architecture.
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

    set(ARM_DEV_DIR /home/ckier/local/)
    link_directories(${ARM_DEV_DIR}browndeer/lib ${ARM_DEV_DIR}log4cpp)
endif ()

set(SOURCE_FILES main.cpp)
add_executable(para_run ${SOURCE_FILES})
include_directories(ExploreOpenCL)
add_subdirectory(ExploreOpenCL)
target_link_libraries(para_run ExploreOpenCL)

#if (CONFIG_ARCH STREQUAL amd64)
##    include_directories(/opt/googletest/include)
##    link_directories(/opt/googletest/lib)
#
#    set(OPENCL_LIBS OpenCL)
#    set(LOGGER_LIBS log4cpp)
#    set(TEST_LIBS gtest pthread)
#
#    add_definitions(-DDEVICE_TYPE=CL_DEVICE_TYPE_ALL)
#    add_definitions(-DREQUESTED_NUMBER_DEVICES=5)
#
##    add_subdirectory(ExploreOpenCLTest)
#endif ()

if (DEBUG)
    message(STATUS "xxxxxxxxxxxx: CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
    message(STATUS "xxxxxxxxxxxx: CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
    message(STATUS "xxxxxxxxxxxx: CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    message(STATUS "xxxxxxxxxxxx: CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}")

    #Uncomment the following line to see variable output in Clion.
    #message(FATAL_ERROR "CMake Killed for variable inspection.")
endif ()
