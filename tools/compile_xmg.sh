mkdir ../build

cmake \
    -D CMAKE_BUILDTYPE=Debug \
    -D NUM_BUILD_JOBS=2 \
    -D BUILD_RT_PROJECT=OFF \
    ../build

