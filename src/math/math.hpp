#pragma once
#include <cstdio>
#include <vector>

namespace math
{
void test();
template <typename T> std::vector<T> linspace(T start, T end, size_t count);
} // namespace math