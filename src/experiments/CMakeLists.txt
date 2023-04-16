
# Executables
rt_exe(
  NAME precision
  HEADERS precision/precision.hpp
  SOURCES precision/main.cpp 
  DEPENDENCIES OpenVDB::openvdb rt::logging rt::math DataFrame::DataFrame
  )

rt_exe(
  NAME img_sim
  SOURCES img_sim/main.cpp
  DEPENDENCIES OpenVDB::openvdb rt::logging rt::math
)
