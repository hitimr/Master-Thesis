#pragma once
#include <vector>

namespace math
{
template <typename T> std::vector<T> linspace(T start, T end, size_t count) { return std::vector<T>(count); }
} // namespace math
