
# Executables
rt_exe(
  NAME precision
  HEADERS precision/precision.hpp
  SOURCES precision/main.cpp 
  DEPENDENCIES OpenVDB::openvdb rt::logging rt::math DataFrame::DataFrame
  )
