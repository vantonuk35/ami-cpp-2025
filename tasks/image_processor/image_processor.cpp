#include "BmpIO.h"
#include "CImage.h"
#include "FilterFabric.h"

#include <iostream>
#include <map>

int main(int argc, char** argv) {
    try {
        if (argc < 3) {
            std::cout << "Please specify launch args: \n";
            std::cout << argv[0] << " {input filename} {output filename}";
            std::cout << " [-{filter name 1} [filter param1] [filter param2] ...]";
            std::cout << " [-{filter name 2}...] ..." << std::endl;

            FilterFabric::PrintManual();

            return 0;
        }
        if (argc >= 4 && argv[3][0] != '-') {
            throw std::runtime_error("Invalid args. You should specify filter right after output file");
        }
        std::vector<std::pair<std::string, std::vector<std::string>>> requested_filters;

        for (int i = 3; i < argc; ++i) {
            if (argv[i][0] == '-') {
                requested_filters.push_back({argv[i], {}});
                continue;
            }
            requested_filters.back().second.push_back(argv[i]);
        }

        CImage image = BmpIO::Load(argv[1]);
        for (const auto& [filter_name, filter_args] : requested_filters) {
            auto filter = FilterFabric::Create(filter_name.substr(1));
            filter->Process(image, filter_args);
        }
        BmpIO::Save(image, argv[2]);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
