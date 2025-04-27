#pragma once

#include <string>
#include "../filter.h"

class Crop : public Filter {
public:
    void Apply(Image& image, std::vector<std::string>& arguments) override;
};
