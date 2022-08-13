#include "logging/logging.hpp"
#include "math/math.hpp"

#include <nanovdb/util/CudaDeviceBuffer.h>
#include <nanovdb/util/Primitives.h>
#include <nanovdb/util/Ray.h>

#include <iostream>
#include <vector>

#ifdef NANOVDB_USE_CUDA
using BufferT = nanovdb::CudaDeviceBuffer;
#else
using BufferT = nanovdb::HostBuffer;
#endif

#define ORIGIN (0., 0., 0.)

#define SPHERE_RADIUS 10.
#define SPHERE_CENTER (30., 0., 0.)
#define VOXEL_SIZE 0.1
#define HALFWIDTH 3 * VOXEL_SIZE

#define RAY_COUNT 1000
#define RAY_START_Z -5.
#define RAY_END_Z 5.

using RayT = nanovdb::Ray<float>;
using Vec3T = nanovdb::Vec3f;

int main()
{
  logging::init();

  // Generate Sphere
  PLOG_INFO << "Generating Sphere" << std::endl;
  nanovdb::GridHandle<BufferT> grid_handle;
  grid_handle = nanovdb::createLevelSetSphere<float, float, BufferT>(SPHERE_RADIUS, nanovdb::Vec3f(SPHERE_RADIUS),
                                                                     VOXEL_SIZE, HALFWIDTH);

  // Generate Rays
  PLOG_INFO << "Generating Rays" << std::endl;
  auto origins_z = math::linspace(RAY_START_Z, RAY_END_Z, RAY_COUNT);
  std::vector<nanovdb::Ray<float>> rays(RAY_COUNT);

  for (int i = 0; i < RAY_COUNT; i++)
  {
    Vec3T origin(0., 0., origins_z[i]);
    Vec3T eye(1., 0., 0.);
    // rays[i] = RayT(origin, eye).worldToIndexF(*grid_handle);
  }

  // auto acc = grid_handle.tree().getAccessor();

  // Perform intersection

  return 0;
}