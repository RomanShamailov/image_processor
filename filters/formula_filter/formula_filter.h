#pragma once

#include <string>
#include "../filter.h"

class FormulaFilter : virtual public Filter {
public:
    virtual Pixel Formula(Pixel pixel) = 0;

    void Apply(Image& image, std::vector<std::string>& arguments) override;
};
