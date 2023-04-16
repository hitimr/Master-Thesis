
# Executables
rt_exe(
  NAME precision
  HEADERS precision/precision.hpp
  SOURCES precision/main.cpp 
  DEPENDENCIES 
    DataFrame::DataFrame
    OpenVDB::openvdb 
    rt::logging 
    rt::math 
  )

rt_exe(
  NAME img_sim
  SOURCES img_sim/main.cpp
  DEPENDENCIES 
    OpenVDB::openvdb 
    ${OpenCV_LIBS}
    rt::logging 
    rt::math 
)
