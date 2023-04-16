echo "Building vdb_view"
cd build
cmake \
    -D CMAKE_BUILD_TYPE=Release \
    -D NUM_BUILD_JOBS=8 \
    -D BUILD_PYOPENVDB=ON \ 
    ..
make
cd ..

echo "Installing pyopenvdb"
INSTALL_DIR=$(ls -d /home/$USER/.local/lib/python3.*)/site-packages
LIB_FILE=$(ls -d build/external/openvdb/lib/python3.*)/dist-packages/pyopenvdb.so
mkdir -p $INSTALL_DIR
cp "$LIB_FILE" "$INSTALL_DIR"/pyopenvdb.so