#pragma once

#include "../matrix_filter/matrix_filter.h"
#include <string>

class Sharpening : public MatrixFilter {
public:
    void Apply(Image& image, std::vector<std::string>& arguments) override;
};
