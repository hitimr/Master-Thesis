mkdir -p ../build
cd ../build

cmake \
    -DCMAKE_BUILD_TYPE=Debug \
    -DNUM_BUILD_JOBS=8 \
    -DCMAKE_CUDA_ARCHITECTURES=52 \
    -DBUILD_DEPENDENCIES=ON \
    -DBUILD_RT_PROJECT=OFF \
    ..

make

cmake \
    -DBUILD_DEPENDENCIES=OFF \
    -DBUILD_RT_PROJECT=ON \
    ..
make

cd ../tools
