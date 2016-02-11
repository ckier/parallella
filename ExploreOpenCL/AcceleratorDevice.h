///
/// \file AcceleratorDevice.h
/// \copyright copyright &copy;2015 Device Controls for Scientific Research, LLC
///

#pragma once

#include <CL/cl.h>
#include <string>
#include <log4cpp/Category.hh>

namespace Parallella {

/// \brief Class to initialize and control the accelerator device.
class AcceleratorDevice {
 public:
  AcceleratorDevice(log4cpp::Category* logger);
  virtual ~AcceleratorDevice();

 private:
  log4cpp::Category* logger_;
  cl_platform_id platform_;
  cl_device_id device_;
  cl_context context_;
  void InitializePlatform();
  void InitializeDevices();
  void InitializeContexts();
  void PrintPlatformInfo(cl_platform_info info, const std::string& message) const;
  void PrintDeviceInfo(cl_device_info info, const std::string& message) const;
  void PrintContextInfo(cl_context_info info, const std::string& message) const;
};
}  // namespace Parallella
