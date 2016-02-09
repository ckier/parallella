///
/// \file main.cpp
/// \copyright copyright &copy;2015 Device Controls for Scientific Research, LLC
///

#include "AcceleratorDevice.h"
#include "Utilities.h"

int main(int argc, char** argv);

///
/// \brief The main entry point.
///
int main(int argc, char** argv) {
  log4cpp::Category* logger = Parallella::GetLogger();
  *logger << log4cpp::Priority::INFO << "Parallella processing started.";

  // Get the OpenCL device and start processing.
  Parallella::AcceleratorDevice device(logger);

  *logger << log4cpp::Priority::INFO << "Parallella processing finished.";
  return 0;
}
