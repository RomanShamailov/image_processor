#pragma once

#include <algorithm>
#include <string>
#include "../filter.h"

const FourBytes MATRIX_SIZE = 9;
const FourBytes TOP_LEFT = 0;
const FourBytes TOP_MIDDLE = 1;
const FourBytes TOP_RIGHT = 2;
const FourBytes MIDDLE_LEFT = 3;
const FourBytes MIDDLE = 4;
const FourBytes MIDDLE_RIGHT = 5;
const FourBytes BOTTOM_LEFT = 6;
const FourBytes BOTTOM_MIDDLE = 7;
const FourBytes BOTTOM_RIGHT = 8;

class MatrixFilter : virtual public Filter {
public:
    void Apply(Image& image, std::vector<std::string>& arguments) override;
};
