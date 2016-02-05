include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(para_run_tests AccleratorDeviceTest.cpp)

target_link_libraries(para_run_tests gtest gtest_main)
target_link_libraries(para_run_tests ExploreOpenCL)