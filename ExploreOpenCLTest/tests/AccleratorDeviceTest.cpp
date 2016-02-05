///
/// \file AcceleratorDeviceTest.cpp
/// \copyright copyright &copy;2015 Device Controls for Scientific Research, LLC
///

#include "gtest/gtest.h"
#include "Utilities.h"

TEST(LoggerTestCase, Test_GetLogger) {
  log4cpp::Category* logger = Parallella::ExploreOpenCL::Utilities::GetLogger();
  EXPECT_TRUE(logger != nullptr);
  delete logger;
}
