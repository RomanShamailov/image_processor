#include "grayscale.h"

Pixel Grayscale::Formula(Pixel pixel) {
    float new_value =
        COEFFICIENT_1 * pixel.GetRed() + COEFFICIENT_2 * pixel.GetGreen() + COEFFICIENT_3 * pixel.GetBlue();
    return Pixel(new_value, new_value, new_value);
}

void Grayscale::Apply(Image& image, std::vector<std::string>& arguments) {
    FormulaFilter::Apply(image, arguments);
}
