#pragma once

#include <string>
#include "../formula_filter/formula_filter.h"

class Negative : public FormulaFilter {
public:
    Pixel Formula(Pixel pixel) override;

    void Apply(Image& image, std::vector<std::string>& arguments) override;
};
