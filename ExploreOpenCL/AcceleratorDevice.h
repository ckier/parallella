// Copyright (C) 2016 Christian K. Kier (chris.kier@devicecontrols.com)
//
// This file is part of the Parallella project.
//
// Parallella is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Foobar is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

///
/// \file AcceleratorDevice.h
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
