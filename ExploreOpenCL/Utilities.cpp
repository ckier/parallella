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
/// \file Utilities.cpp
/// \brief Application utility functions.
///

#include <string>
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "Utilities.h"

namespace Parallella {

static const char* const loggerName = "ExploreOpenCL";
static const char* const logFileName = "program.log";
static log4cpp::Category& logger = log4cpp::Category::getInstance(std::string(loggerName));
static log4cpp::Category* loggerPtr = nullptr;

/// \brief Get the logger for the application.
/// \retval logger A pointer to the application logger.
log4cpp::Category* GetLogger() {
  if (loggerPtr != nullptr) {
    return loggerPtr;
  }
  auto consoleAppender = new log4cpp::OstreamAppender("console", &std::cout);
  consoleAppender->setLayout(new log4cpp::BasicLayout());

  auto fileAppender = new log4cpp::FileAppender("default", logFileName);
  fileAppender->setLayout(new log4cpp::BasicLayout());

  logger.setPriority(log4cpp::Priority::DEBUG);
  logger.addAppender(consoleAppender);
  logger.addAppender(fileAppender);

  loggerPtr = &logger;
  return loggerPtr;
}

}  // namespace Parallella
