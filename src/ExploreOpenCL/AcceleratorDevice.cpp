///
/// \file AcceleratorDevice.cpp
/// \copyright copyright &copy;2015 Device Controls for Scientific Research, LLC
///

#include "AcceleratorDevice.h"
#include <iostream>

namespace Parallella {
namespace ExploreOpenCL {

const int kBufferSize = 256;

AcceleratorDevice::AcceleratorDevice() {
  InitializePlatform();
  InitializeDevice();
}

AcceleratorDevice::~AcceleratorDevice() {
}

void AcceleratorDevice::InitializePlatform() {
  const cl_uint kMaxNumberOfPlatforms = 5;

  cl_uint number_of_platforms;
  clGetPlatformIDs(kMaxNumberOfPlatforms, nullptr, &number_of_platforms);
  auto platforms = static_cast<cl_platform_id *>(malloc(
      number_of_platforms * sizeof(cl_platform_id)));
  clGetPlatformIDs(number_of_platforms, platforms, 0);
  std::cout << "Number of platforms: " << number_of_platforms << std::endl;

  auto index = 0;
  for (auto i = 0; i < number_of_platforms; i++) {
    PrintPlatformInfo(platforms[i], CL_PLATFORM_NAME, "name");
    PrintPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, "vendor");
    PrintPlatformInfo(platforms[i], CL_PLATFORM_VERSION, "version");
    PrintPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, "profile");
    PrintPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, "extensions");
    index = i;
  }

  if (index < number_of_platforms) {
    platform_ = platforms[index];
  } else {
    perror("No opencl platform available.");
    exit(1);
  }
  free(platforms);
}

void AcceleratorDevice::PrintPlatformInfo(cl_platform_id id,
                                          cl_platform_info info,
                                          std::string message) {
  char buffer[kBufferSize];
  clGetPlatformInfo(id, info, sizeof(buffer), &buffer, nullptr);
  std::cout << "Platform " << message << ": " << buffer << std::endl;
}

void AcceleratorDevice::InitializeDevice() {
  cl_uint number_of_devices;
  clGetDeviceIDs(platform_,
                 DEVICE_TYPE,
                 REQUESTED_NUMBER_DEVICES,
                 nullptr,
                 &number_of_devices);
  std::cout << std::endl << "Number of devices: " << number_of_devices
      << std::endl;

  auto devices = static_cast<cl_device_id *>(malloc(
      sizeof(cl_device_id) * number_of_devices));
  clGetDeviceIDs(platform_, DEVICE_TYPE, number_of_devices, devices, nullptr);

  if (number_of_devices > 0) {
    device_ = devices[0];
    PrintDeviceInfo(device_, CL_DEVICE_NAME, "name");
    PrintDeviceInfo(device_, CL_DEVICE_VENDOR, "vendor");
    PrintDeviceInfo(device_, CL_DEVICE_EXTENSIONS, "extensions");
    PrintDeviceInfo(device_,
                    CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
                    "global memory size");
    PrintDeviceInfo(device_, CL_DEVICE_ADDRESS_BITS, "address bits");
    PrintDeviceInfo(device_, CL_DEVICE_AVAILABLE, "available");
    PrintDeviceInfo(device_,
                    CL_DEVICE_COMPILER_AVAILABLE,
                    "compiler available");
  } else {
    perror("No opencl device available.");
    exit(1);
  }
  free(devices);
}
void AcceleratorDevice::PrintDeviceInfo(cl_device_id id,
                                        cl_device_info info,
                                        std::string message) {
  char buffer[kBufferSize];
  cl_ulong ulong_return_value;
  cl_uint uint_return_value;
  cl_bool bool_return_value;

  switch (info) {
    case CL_DEVICE_NAME:
    case CL_DEVICE_VENDOR:
    case CL_DEVICE_EXTENSIONS:
      clGetDeviceInfo(id, info, sizeof(buffer), &buffer, nullptr);
      std::cout << "Device " << message << ": " << buffer << std::endl;
      break;
    case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:
      clGetDeviceInfo(id, info, sizeof(cl_ulong), &ulong_return_value, nullptr);
      std::cout << "Device " << message << ": " << ulong_return_value
          << std::endl;
      break;
    case CL_DEVICE_ADDRESS_BITS:
      clGetDeviceInfo(id, info, sizeof(cl_uint), &uint_return_value, nullptr);
      std::cout << "Device " << message << ": " << uint_return_value
          << std::endl;
      break;
    case CL_DEVICE_AVAILABLE:
    case CL_DEVICE_COMPILER_AVAILABLE:
      clGetDeviceInfo(id, info, sizeof(cl_bool), &bool_return_value, nullptr);
      std::cout << "Device " << message << ": " << bool_return_value
          << std::endl;
      break;
    default:
      perror("Device info not recognized.");
      break;
  }
}

}  // namespace ExploreOpenCL
}  // namespace Parallella
