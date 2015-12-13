///
/// \file AcceleratorDevice.h
/// \copyright copyright &copy;2015 Device Controls for Scientific Research, LLC
///

#pragma once

#include <CL/cl.h>
#include <string>
#include <log4cpp/Category.hh>

namespace Parallella {
namespace ExploreOpenCL {

/// \brief Class to initialize and control the accelerator device.
class AcceleratorDevice {
 public:
  AcceleratorDevice(log4cpp::Category* logger);
  virtual ~AcceleratorDevice();

 private:
  log4cpp::Category* logger_;
  cl_platform_id platform_;
  cl_device_id device_;
  void InitializePlatform();
  void InitializeDevices();
  void PrintPlatformInfo(cl_platform_id id, cl_platform_info info, std::string message);
  void PrintDeviceInfo(cl_device_id id, cl_device_info info, std::string message);
};
}  // namespace ExploreOpenCL
}  // namespace Parallella
