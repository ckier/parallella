cmake_minimum_required(VERSION 3.0)
project(Parallella)

# Set to ON to make debug output active, Off otherwise.
set(DEBUG ON)

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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CONFIG_ARCH}/${CMAKE_BUILD_TYPE})
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -std=c++11")

add_definitions(-DDEVICES_TO_DISPLAY=1)

if (CONFIG_ARCH STREQUAL amd64)
    include_directories(/opt/googletest/include)
    link_directories(/opt/googletest/lib)

    set(OPENCL_LIBS OpenCL)
    set(LOGGER_LIBS log4cpp)
    set(TEST_LIBS gtest pthread)

    add_definitions(-DDEVICE_TYPE=CL_DEVICE_TYPE_ALL)
    add_definitions(-DREQUESTED_NUMBER_DEVICES=5)

    add_subdirectory(src/HelloWorld)
    add_subdirectory(src/ExploreOpenCL)
    add_subdirectory(src/VectorMultiply)
endif ()

if (CONFIG_ARCH STREQUAL arm)
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)
    set(ARM_DEV_DIR /home/ckier/local/)

    include_directories(${ARM_DEV_DIR}googletest/include)
    link_directories(${ARM_DEV_DIR}googletest/lib)
    link_directories(${ARM_DEV_DIR}browndeer/lib ${ARM_DEV_DIR}log4cpp)

    set(OPENCL_LIBS libcoprthr_opencl.so)
    set(LOGGER_LIBS log4cpp)
    set(TEST_LIBS gtest pthread)

    add_definitions(-DDEVICE_TYPE=CL_DEVICE_TYPE_ACCELERATOR)
    add_definitions(-DREQUESTED_NUMBER_DEVICES=0)

    add_subdirectory(src/ExploreOpenCL)
    add_subdirectory(src/HelloWorld)
    add_subdirectory(src/VectorMultiply)

    # The following lines should allow us to find library
    # and include file resources, but they do not seem to work.
    #    set(CMAKE_FIND_ROOT_PATH
    #            /usr/lib/arm-linux-gnueabihf
    #            /usr/include/arm-linux-gnueabihf
    #            /home/ckier/local/browndeer/include
    #            /home/ckier/local/browndeer/lib)
    #
    #    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    #    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    #    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif ()

if (DEBUG)
    message(STATUS "xxxxxxxxxxxx: CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
    message(STATUS "xxxxxxxxxxxx: CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
    message(STATUS "xxxxxxxxxxxx: CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    message(STATUS "xxxxxxxxxxxx: CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}")

    #Uncomment the following line to see variable output in Clion.
    #message(FATAL_ERROR "CMake Killed for variable inspection.")
endif ()
