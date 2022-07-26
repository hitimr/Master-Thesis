#include <benchmarker/benchmarker.hpp>
#include <openvdb/openvdb.h>
#include <util/logging.hpp>

int main()
{
  logging::init();

  PLOG_VERBOSE << "This is a VERBOSE message";
  PLOG_DEBUG << "This is a DEBUG message";
  PLOG_INFO << "This is an INFO message";
  PLOG_WARNING << "This is a WARNING message";
  PLOG_ERROR << "This is an ERROR message";
  PLOG_FATAL << "This is a FATAL message";

  return 0;
}