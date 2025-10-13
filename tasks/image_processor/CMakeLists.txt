set(CMAKE_CXX_STANDARD 20)
add_executable(
        image_processor
        image_processor.cpp
        BmpIO.cpp
        BmpIO.h
        CImage.cpp
        CImage.h
        IFilter.h
        FilterFabric.cpp
        FilterFabric.h
        CropFilter.cpp
        SharpeningFilter.cpp
        NegativeFilter.cpp
        GrayscaleFilter.cpp
        GaussianFilter.cpp
        EdgeFilter.cpp
        FisheyeFilter.cpp
)

