#include <util/logging.hpp>

#include <nanovdb/util/CudaDeviceBuffer.h>
// #include <nanovdb/util/IO.h>
#include <nanovdb/util/Primitives.h>

#include <iostream>

#ifdef NANOVDB_USE_CUDA
using BufferT = nanovdb::CudaDeviceBuffer;
#else
using BufferT = nanovdb::HostBuffer;
#endif

int main()
{
  logging::init();

  nanovdb::GridHandle<BufferT> handle;
  handle = nanovdb::createLevelSetSphere<float, float, BufferT>(100.0f, nanovdb::Vec3f(-20, 0, 0), 1.0, 3.0,
                                                                nanovdb::Vec3d(0), "sphere");

#ifdef NANOVDB_USE_CUDA
  std::cout << "using NanoVDB" << std::endl;
#else
  std::cout << "Not using CUDA" << std::endl;
#endif

  return 0;
}