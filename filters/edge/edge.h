#pragma once

#include "../grayscale/grayscale.h"
#include "../matrix_filter/matrix_filter.h"
#include <string>

class Edge : public MatrixFilter, public Grayscale {
public:
    void Apply(Image& image, std::vector<std::string>& arguments) override;
};
