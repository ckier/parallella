set(SOURCE_FILES hello-opencl.cpp)
add_executable(VectorMultiply ${SOURCE_FILES})
target_link_libraries(VectorMultiply ${OPENCL_LIBS})
