#include "logging.hpp"

void logging::init()
{
  static plog::ColorConsoleAppender<plog::TxtFormatterUtcTime> consoleAppender; // TxtFormatter in UTC
  static plog::RollingFileAppender<plog::CsvFormatterUtcTime> fileAppender("UtcTime.csv", 10000,
                                                                           2); // CsvFormatter in UTC
  plog::init(plog::verbose, &consoleAppender).addAppender(&fileAppender);
}