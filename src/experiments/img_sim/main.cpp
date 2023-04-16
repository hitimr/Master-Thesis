#include "stdafx.hpp"
#include "img_sim.hpp"



int main()
{
    openvdb::initialize();
    openvdb::io::File file("build/grids/sensor_1920x1080.vdb");
    
    file.open();

    openvdb::GridBase::Ptr baseGrid;
    for (openvdb::io::File::NameIterator nameIter = file.beginName();
        nameIter != file.endName(); ++nameIter)
    {
        // Read in only the grid we are interested in.
        if (nameIter.gridName() == "sensor") {
            baseGrid = file.readGrid(nameIter.gridName());
        } else {
            std::cout << "skipping grid " << nameIter.gridName() << std::endl;
        }
    }
    file.close();

    // convert basegrid to OpenGridT
    OpenGridT::Ptr grid = openvdb::gridPtrCast<OpenGridT>(baseGrid);


    cv::Mat image = cv::imread("data/img/Lenna.png");
    cv::imshow("Image", image);
    cv::waitKey();

    return 0;
} 