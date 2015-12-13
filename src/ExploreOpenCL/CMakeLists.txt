set(SOURCE_FILES main.cpp AcceleratorDevice.cpp Utilities.cpp)
add_executable(ExploreOpenCL ${SOURCE_FILES})
target_link_libraries(ExploreOpenCL ${OPENCL_LIBS} ${LOGGER_LIBS})
