#include "negative.h"

Pixel Negative::Formula(Pixel pixel) {
    return Pixel(1 - pixel.GetRed(), 1 - pixel.GetGreen(), 1 - pixel.GetBlue());
}

void Negative::Apply(Image& image, std::vector<std::string>& arguments) {
    FormulaFilter::Apply(image, arguments);
}
