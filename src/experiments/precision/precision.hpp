#pragma once
#include <logging/logging.hpp>
#include <math/math.hpp>

#include <DataFrame/DataFrame.h>
#include <DataFrame/DataFrameTypes.h>
#include <nanovdb/NanoVDB.h>
#include <nanovdb/util/GridHandle.h>
#include <nanovdb/util/HDDA.h>
#include <nanovdb/util/OpenToNanoVDB.h>
#include <nanovdb/util/Primitives.h>
#include <nanovdb/util/Ray.h>
#include <openvdb/math/Ray.h>
#include <openvdb/openvdb.h>
#include <openvdb/tools/LevelSetSphere.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#define ORIGIN (0., 0., 0.)

#define SPHERE_RADIUS 5.
#define SPHERE_CENTER_X 10.
#define SPHERE_CENTER_Y 0.
#define SPHERE_CENTER_Z 0.
#define VOXEL_SIZE 0.1
#define HALFWIDTH 3

#define RAY_COUNT 1000
#define RAY_START_Z -5.
#define RAY_END_Z 5.

using OpenRayT = openvdb::math::Ray<float>;
using NanoRayT = nanovdb::Ray<float>;
using NanoVec3T = nanovdb::Vec3f;
using OpenVec3T = openvdb::Vec3f;
using OpenGridT = openvdb::FloatGrid;
using NanoGridT = nanovdb::FloatGrid;
using NanoCoordT = nanovdb::Coord;
using NanoBufferT = nanovdb::HostBuffer;
using ULDataFrame = hmdf::StdDataFrame<unsigned long>;
