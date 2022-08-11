#include <benchmarker/benchmarker.hpp>
#include <openvdb/openvdb.h>
#include <util/logging.hpp>


int main()
{
      logging::init();
    cudaDeviceSynchronize();
    return 0;
}