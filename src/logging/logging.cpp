#include "logging.hpp"

#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/CsvFormatter.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>

void init()
{
  static plog::ColorConsoleAppender<plog::TxtFormatterUtcTime> consoleAppender; // TxtFormatter in UTC
  static plog::RollingFileAppender<plog::CsvFormatterUtcTime> fileAppender("UtcTime.csv", 10000,
                                                                           2); // CsvFormatter in UTC
  plog::init(plog::verbose, &consoleAppender).addAppender(&fileAppender);
}