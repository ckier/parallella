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
/// \file main.cpp
///

#include <string>
#include <algorithm>
#include <getopt.h>
#include "AcceleratorDevice.h"
#include "Utilities.h"

using LogPriority = log4cpp::Priority;

static LogPriority::PriorityLevel GetLogLevelFromString(std::string& option_log_level) {
  LogPriority::PriorityLevel log_level;
  std::transform(option_log_level.begin(),
                 option_log_level.end(),
                 option_log_level.begin(),
                 toupper);
  if (option_log_level.compare("ERROR") == 0) {
    log_level = LogPriority::ERROR;
  } else if (option_log_level.compare("WARN") == 0) {
    log_level = LogPriority::WARN;
  } else if (option_log_level.compare("INFO") == 0) {
    log_level = LogPriority::INFO;
  } else {
    log_level = LogPriority::DEBUG;
  }
  return log_level;
}

///
/// \brief The main entry point.
///
int main(int argc, char** argv) {
  auto option = 0;
  std::string option_log_level;
  LogPriority::PriorityLevel log_level = LogPriority::DEBUG;

  struct option longopts[] = {
      {"log-level", required_argument, nullptr, 'L'},
      {0, 0, 0, 0}
  };

  while ((option = getopt_long(argc, argv, ":L:", longopts, nullptr)) != -1) {
    switch (option) {
      case 'L':
        option_log_level = optarg;
        log_level = GetLogLevelFromString(option_log_level);
        break;
      case 0:
        break;
      case ':':
        std::cout << "Option: -" << static_cast<char>(optopt) << " requires an argument"
            << std::endl;
        exit(EXIT_FAILURE);
      case '?':
      default:
        std::cout << "Usage: para_run -l [DEBUG|INFO|WARN|ERROR]" << std::endl;
        exit(EXIT_FAILURE);
    }
  }

  log4cpp::Category* logger = Parallella::GetLogger();
  logger->setPriority(log_level);
  *logger << LogPriority::INFO << "Parallella processing started.";

  // Get the OpenCL device and start processing.
  Parallella::AcceleratorDevice device(logger);

  *logger << LogPriority::INFO << "Parallella processing finished.";
  return EXIT_SUCCESS;
}
