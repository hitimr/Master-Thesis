#include "precision.hpp"

NanoVec3T indexToWorld(NanoCoordT &index, nanovdb::GridHandle<NanoBufferT> grid_handle)
{
  auto grid = grid_handle.grid<float>();
  return NanoVec3T(index[0] * grid->voxelSize()[0], index[1] * grid->voxelSize()[1], index[2] * grid->voxelSize()[2]);
}

int main()
{
  logging::init();

  // Generate Sphere
  PLOG_INFO << "Generating Sphere";
  OpenGridT sphere = *openvdb::tools::createLevelSetSphere<OpenGridT>(
      SPHERE_RADIUS, OpenVec3T(SPHERE_CENTER_X, SPHERE_CENTER_Y, SPHERE_CENTER_Z), VOXEL_SIZE, HALFWIDTH);
  nanovdb::GridHandle<NanoBufferT> nano_sphere = nanovdb::openToNanoVDB<NanoBufferT>(sphere);
  auto grid = nano_sphere.grid<float>();

  // Generate Rays
  PLOG_INFO << "Generating Rays";
  auto origins_z = math::linspace<float>(RAY_START_Z, RAY_END_Z, RAY_COUNT);
  std::vector<NanoRayT> iRays(RAY_COUNT);

  for (int i = 0; i < RAY_COUNT; i++)
  {
    NanoVec3T eye(0, 0, origins_z[i]);
    NanoVec3T direction(1, 0, 0);
    NanoRayT ray(nano_sphere.grid<float>()->worldToIndex(eye), direction);
    iRays[i] = ray;
  }

  // Calculate analytical solution
  PLOG_INFO << "Calculating analytical solution";
  std::vector<float> gt_intersect_x(RAY_COUNT);
  std::vector<float> gt_intersect_y(RAY_COUNT);
  std::vector<float> alpha_vals = math::linspace<float>(1.5 * M_PI, 0.5 * M_PI, RAY_COUNT);
  for (int i = 0; i < RAY_COUNT; i++)
  {
    gt_intersect_x[i] = SPHERE_CENTER_X + SPHERE_RADIUS * std::cos(alpha_vals[i]);
    gt_intersect_y[i] = SPHERE_CENTER_Y + SPHERE_RADIUS * std::sin(alpha_vals[i]);
  }

  // Perform Ray Intersection
  PLOG_INFO << "Performing Ray intersection";
  std::vector<float> values(RAY_COUNT);
  std::vector<float> times(RAY_COUNT);
  std::vector<NanoCoordT> coords(RAY_COUNT);
  std::vector<float> idx_x(RAY_COUNT);
  std::vector<float> idx_y(RAY_COUNT);
  std::vector<float> intersect_x(RAY_COUNT);
  std::vector<float> intersect_y(RAY_COUNT);
  auto accessor = nano_sphere.grid<float>()->tree().getAccessor();
  for (int i = 0; i < RAY_COUNT; i++)
  {
    nanovdb::ZeroCrossing(iRays[i], accessor, coords[i], values[i], times[i]);
    idx_x[i] = (float)coords[i].x();
    idx_y[i] = (float)coords[i].y();

    // Transform intersection point back to world space
    // NanoVec3T wIntersect = indexToWorld(coords[i], nano_sphere);
    auto wIntersect = grid->indexToWorld(coords[i].asVec3s());
    intersect_x[i] = wIntersect[0];
    intersect_y[i] = wIntersect[2];
  }

  // write Data To File
  PLOG_INFO << "Writing Data to File";
  ULDataFrame df;
  std::vector<size_t> idx(RAY_COUNT);
  std::iota(idx.begin(), idx.end(), 0);

  // clang-format off
  df.load_data(
    std::move(idx), 
    std::make_pair("origin_z", origins_z), 
    std::make_pair("intersect_x", intersect_x),
    std::make_pair("intersect_y", intersect_y),
    std::make_pair("idx_x", idx_x),
    std::make_pair("idx_y", idx_y),
    std::make_pair("value", values),
    std::make_pair("time", times),
    std::make_pair("gt_intersect_x", gt_intersect_x),
    std::make_pair("gt_intersect_y", gt_intersect_y)
    );

  df.write<
    size_t, 
    float>
    ("data.csv", hmdf::io_format::csv2);
  //clang-format on
  return 0;
}