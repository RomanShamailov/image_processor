#include "formula_filter.h"

void FormulaFilter::Apply(Image& image, std::vector<std::string>& arguments) {
    for (FourBytes y = 0; y < image.GetHeight(); ++y) {
        for (FourBytes x = 0; x < image.GetWidth(); ++x) {
            image.SetPixel(x, y, Formula(image.GetPixel(x, y)));
        }
    }
}
