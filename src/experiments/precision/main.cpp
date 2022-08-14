#include "precision.hpp"

int main()
{
  logging::init();

  // Generate Sphere
  PLOG_INFO << "Generating Sphere";
  OpenGridT sphere =
      *openvdb::tools::createLevelSetSphere<OpenGridT>(SPHERE_RADIUS, OpenVec3T(0, 0, 0), VOXEL_SIZE, HALFWIDTH);
  auto nano_sphere = nanovdb::openToNanoVDB<NanoBufferT>(sphere).grid<float>();

  // Generate Rays
  PLOG_INFO << "Generating Rays";
  auto origins_z = math::linspace(RAY_START_Z, RAY_END_Z, RAY_COUNT);
  std::vector<NanoRayT> iRays(RAY_COUNT);

  for (int i = 0; i < RAY_COUNT; i++)
  {
    NanoVec3T origin(0., 0., origins_z[i]); // Rays are spread alog the z-Axis
    NanoVec3T direction(1., 0., 0.);        // All rays are parallel to the x-Axis
    iRays[i] = NanoRayT(nano_sphere->worldToIndex(origin), direction);
  }

  // Perform Ray Intersection
  int i = 0;
  std::vector<float> values(RAY_COUNT);
  std::vector<float> times(RAY_COUNT);
  std::vector<NanoCoordT> coords;
  auto accessor = nano_sphere->tree().getAccessor();
  nanovdb::ZeroCrossing(iRays[i], accessor, coords[i], values[i], times[i]);

  return 0;
}