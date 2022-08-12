#include "logging/logging.hpp"

#include <nanovdb/util/CudaDeviceBuffer.h>
#include <nanovdb/util/Primitives.h>

#include <iostream>
#include <vector>

#ifdef NANOVDB_USE_CUDA
using BufferT = nanovdb::CudaDeviceBuffer;
#else
using BufferT = nanovdb::HostBuffer;
#endif

#define ORIGIN (0., 0., 0.)

#define SPHERE_RADIUS 10
#define SPHERE_CENTER (30., 0., 0.)
#define VOXEL_SIZE 0.1
#define HALFWIDTH 3 * VOXEL_SIZE

#define RAY_COUNT 1000
#define RAY_START_Z -5.
#define RAY_END_Z -5.

int main()
{
  // logging::init();

  // Generate Sphere
  nanovdb::GridHandle<BufferT> handle;
  handle = nanovdb::createLevelSetSphere<float, float, BufferT>(SPHERE_RADIUS, nanovdb::Vec3f(SPHERE_RADIUS),
                                                                VOXEL_SIZE, HALFWIDTH);

  // Generate Rays

  return 0;
}