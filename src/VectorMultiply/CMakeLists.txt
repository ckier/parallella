set(SOURCE_FILES hello-opencl.cpp)
add_executable(VectorMultiply ${SOURCE_FILES})
target_link_libraries(VectorMultiply libcoprthr_opencl.so)
