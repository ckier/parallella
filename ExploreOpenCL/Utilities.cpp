///
/// \file Utilities.cpp
/// \copyright copyright &copy;2015 Device Controls for Scientific Research, LLC
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
