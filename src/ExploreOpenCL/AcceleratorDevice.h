//
/// \file AcceleratorDevice.h
/// \copyright copyright &copy;2015 Device Controls for Scientific Research, LLC
//

#pragma once

#include <CL/cl.h>
#include <string>

namespace Parallella {
namespace ExploreOpenCL {
class AcceleratorDevice {
 public:
  AcceleratorDevice();
  virtual ~AcceleratorDevice();

 private:
  cl_platform_id platform_;
  cl_device_id device_;
  void InitializePlatform();
  void InitializeDevice();
  void PrintPlatformInfo
      (cl_platform_id id, cl_platform_info info, std::string message);
  void PrintDeviceInfo
      (cl_device_id id, cl_device_info info, std::string message);
};
}  // namespace ExploreOpenCL
}  // namespace Parallella
