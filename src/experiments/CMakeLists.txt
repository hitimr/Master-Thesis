
# Executables
rt_exe(
  NAME precision
  HEADERS precision/precision.hpp
  SOURCES precision/main.cpp precision/precision.cu
  DEPENDENCIES OpenVDB::openvdb rt::logging rt::math
  )
