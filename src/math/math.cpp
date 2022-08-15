#include "math.hpp"

template <typename T> std::vector<T> math::linspace(T start, T end, size_t count)
{
  std::vector<T> vec(count);
  T delta = (end - start) / count;

  for (size_t i = 0; i < count; i++)
  {
    vec[i] = start + (T)i * delta;
  }
  return vec;
}

void math::test() { return; }

// Forward declarations
template std::vector<double> math::linspace(double, double, size_t);
template std::vector<float> math::linspace(float, float, size_t);
