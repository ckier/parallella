///
/// \file AcceleratorDevice.cpp
/// \copyright copyright &copy;2015 Device Controls for Scientific Research, LLC
///

#include "AcceleratorDevice.h"

#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"

namespace Parallella {

const int kBufferSize = 256;

/// \brief Constructor for the AcceleratorDevice class.
/// \param logger The application logger.
AcceleratorDevice::AcceleratorDevice(log4cpp::Category* logger) {
  logger_ = logger;
  InitializePlatform();
  InitializeDevices();
  InitializeContexts();
}

/// \brief Destructor for the AcceleratorDevice class.
AcceleratorDevice::~AcceleratorDevice() {
  clReleaseContext(context_);
}

void AcceleratorDevice::InitializePlatform() {
  const cl_uint kMaxNumberOfPlatforms = 5;

  cl_uint number_of_platforms;
  clGetPlatformIDs(kMaxNumberOfPlatforms, nullptr, &number_of_platforms);
  auto platforms = static_cast<cl_platform_id*>(malloc(
      number_of_platforms * sizeof(cl_platform_id)));
  clGetPlatformIDs(number_of_platforms, platforms, 0);
  *logger_ << log4cpp::Priority::DEBUG << "Number of platforms: " << number_of_platforms;

  if (number_of_platforms > 0) {
    platform_ = platforms[0];
    PrintPlatformInfo(CL_PLATFORM_NAME, "name");
    PrintPlatformInfo(CL_PLATFORM_VENDOR, "vendor");
    PrintPlatformInfo(CL_PLATFORM_VERSION, "version");
    PrintPlatformInfo(CL_PLATFORM_PROFILE, "profile");
    PrintPlatformInfo(CL_PLATFORM_EXTENSIONS, "extensions");
  } else {
    *logger_ << log4cpp::Priority::ERROR << "No OpenCL platforms available.";
    exit(1);
  }
  free(platforms);

  *logger_ << log4cpp::Priority::INFO << "Initializing Parallella platform completed.";
}

void AcceleratorDevice::InitializeDevices() {
  cl_uint number_of_devices;
  clGetDeviceIDs(platform_, DEVICE_TYPE, REQUESTED_NUMBER_DEVICES, nullptr, &number_of_devices);
  *logger_ << log4cpp::Priority::DEBUG << "Number of devices: " << number_of_devices;

  auto devices = static_cast<cl_device_id*>(malloc(sizeof(cl_device_id) * number_of_devices));
  clGetDeviceIDs(platform_, DEVICE_TYPE, number_of_devices, devices, nullptr);

  if (number_of_devices > 0) {
    device_ = devices[0];
    PrintDeviceInfo(CL_DEVICE_NAME, "name");
    PrintDeviceInfo(CL_DEVICE_VENDOR, "vendor");
    PrintDeviceInfo(CL_DEVICE_EXTENSIONS, "extensions");
    PrintDeviceInfo(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, "global memory size");
    PrintDeviceInfo(CL_DEVICE_ADDRESS_BITS, "address bits");
    PrintDeviceInfo(CL_DEVICE_AVAILABLE, "available");
    PrintDeviceInfo(CL_DEVICE_COMPILER_AVAILABLE, "compiler available");
  } else {
    *logger_ << log4cpp::Priority::ERROR << "No OpenCL devices available.";
    exit(1);
  }
  free(devices);

  *logger_ << log4cpp::Priority::INFO << "Initializing Parallella devices completed.";
}

void AcceleratorDevice::InitializeContexts() {
  cl_uint number_of_devices = 1;
  cl_int error;
  cl_context_properties context_properties[3] = {
      CL_CONTEXT_PLATFORM,
      reinterpret_cast<cl_context_properties>(platform_),
      0
  };

  context_ =
      clCreateContext(context_properties, number_of_devices, &device_, nullptr, nullptr, &error);
  if (error == 0) {
    PrintContextInfo(CL_CONTEXT_NUM_DEVICES, "number of devices");
    PrintContextInfo(CL_CONTEXT_REFERENCE_COUNT, "reference count");
  } else {
    *logger_ << log4cpp::Priority::ERROR << "No OpenCL devices available.";
    exit(error);
  }

  *logger_ << log4cpp::Priority::INFO << "Initializing Parallella contexts completed.";
}

void AcceleratorDevice::PrintPlatformInfo(cl_platform_info info, const std::string& message) const {
  char buffer[kBufferSize];
  clGetPlatformInfo(platform_, info, sizeof(buffer), &buffer, nullptr);
  *logger_ << log4cpp::Priority::DEBUG << "Platform " << message << ": " << buffer;
}

void AcceleratorDevice::PrintDeviceInfo(cl_device_info info, const std::string& message) const {
  char buffer[kBufferSize];
  cl_ulong ulong_return_value;
  cl_uint uint_return_value;
  cl_bool bool_return_value;

  switch (info) {
    case CL_DEVICE_NAME:
    case CL_DEVICE_VENDOR:
    case CL_DEVICE_EXTENSIONS:
      clGetDeviceInfo(device_, info, sizeof(buffer), &buffer, nullptr);
      *logger_ << log4cpp::Priority::DEBUG << "Device " << message << ": " << buffer;
      break;
    case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:
      clGetDeviceInfo(device_, info, sizeof(cl_ulong), &ulong_return_value, nullptr);
      *logger_ << log4cpp::Priority::DEBUG << "Device " << message << ": " << ulong_return_value;
      break;
    case CL_DEVICE_ADDRESS_BITS:
      clGetDeviceInfo(device_, info, sizeof(cl_uint), &uint_return_value, nullptr);
      *logger_ << log4cpp::Priority::DEBUG << "Device " << message << ": " << uint_return_value;
      break;
    case CL_DEVICE_AVAILABLE:
    case CL_DEVICE_COMPILER_AVAILABLE:
      clGetDeviceInfo(device_, info, sizeof(cl_bool), &bool_return_value, nullptr);
      *logger_ << log4cpp::Priority::DEBUG << "Device " << message << ": " << bool_return_value;
      break;
    default:
      *logger_ << log4cpp::Priority::ERROR << "Device info not recognized.";
      break;
  }
}

void AcceleratorDevice::PrintContextInfo(cl_context_info info, const std::string& message) const {
  cl_uint uint_return_value;
  clGetContextInfo(context_, info, sizeof(uint_return_value), &uint_return_value, nullptr);
  *logger_ << log4cpp::Priority::DEBUG << "Context " << message << ": " << uint_return_value;
}
}  // namespace Parallella
