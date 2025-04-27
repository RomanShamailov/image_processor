#pragma once

#include <algorithm>
#include "../filter.h"
#include <vector>

class Pixelate : public Filter {
public:
    void Apply(Image& image, std::vector<std::string>& arguments) override;
};
