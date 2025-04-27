#pragma once

#include <string>
#include "../formula_filter/formula_filter.h"

const float COEFFICIENT_1 = 0.299;
const float COEFFICIENT_2 = 0.587;
const float COEFFICIENT_3 = 0.114;

class Grayscale : virtual public FormulaFilter {
public:
    Pixel Formula(Pixel pixel) override;

    void Apply(Image& image, std::vector<std::string>& arguments) override;
};
