set(CMAKE_CXX_STANDARD 23)
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
        Filters/CropFilter.cpp
        Filters/CropFilter.h
        Filters/SharpeningFilter.cpp
        Filters/SharpeningFilter.h
        Filters/NegativeFilter.cpp
        Filters/NegativeFilter.h
        Filters/GrayscaleFilter.cpp
        Filters/GrayscaleFilter.h
        Filters/GaussianFilter.cpp
        Filters/GaussianFilter.h
        Filters/EdgeFilter.cpp
        Filters/EdgeFilter.h
        Filters/FisheyeFilter.cpp
        Filters/FisheyeFilter.h
)

