INSTALL_DIR="/home/$USER/.local/bin"

echo "Building vdb_view"
cd build
cmake \
    -D CMAKE_BUILD_TYPE=Release \
    -D NUM_BUILD_JOBS=8 \
    -D BUILD_VDB_VIEW=ON \
    ..
make
cd ..

echo "Installing vdb_view"
cp build/external/openvdb/bin/vdb_view "$INSTALL_DIR"