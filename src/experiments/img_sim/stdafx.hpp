#pragma once
#include <math/math.hpp>
#include <logging/logging.hpp>

#include <nanovdb/NanoVDB.h>
#include <nanovdb/util/Ray.h>
#include <nanovdb/util/HDDA.h>
#include <nanovdb/util/GridHandle.h>
#include <nanovdb/util/Primitives.h>
#include <nanovdb/util/OpenToNanoVDB.h>

#include <openvdb/openvdb.h>
#include <openvdb/math/Ray.h>
#include <openvdb/tools/LevelSetSphere.h>
#include <openvdb/tools/RayIntersector.h>

#include <opencv2/opencv.hpp>

#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include <iostream>
#include <algorithm>
