#pragma once
#include "stdafx.hpp"

#define NUM_PIXELS_X 1920
#define NUM_PIXELS_Y 1080

#define VOXEL_SIZE 1
#define HALFWIDTH 3

struct Pixel
{
    uint32_t R;
    uint32_t G;
    uint32_t B;
};

using NanoVec3T = nanovdb::Vec3f;
using NanoCoordT = nanovdb::Coord;
using NanoRayT = nanovdb::Ray<float>;
using NanoBufferT = nanovdb::HostBuffer;

using NanoGridT = nanovdb::FloatGrid;
using OpenGridT = openvdb::FloatGrid;
using PixelTree = nanovdb::NanoTree<Pixel>;