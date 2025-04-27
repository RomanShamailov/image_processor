#pragma once

#include <algorithm>
#include <cmath>
#include "../filter.h"
#include <vector>

const float PI = 3.14159265358979323846;
const float E = 2.71828182845904523536;
const float TWO = 2.0;
const float MINUS_ONE_HALF = -0.5;

class Blur : public Filter {
public:
    void Apply(Image& image, std::vector<std::string>& arguments) override;
};
