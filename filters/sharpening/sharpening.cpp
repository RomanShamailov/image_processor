#include "sharpening.h"

void Sharpening::Apply(Image& image, std::vector<std::string>& arguments) {
    std::vector<std::string> sharpening_values = {"0", "-1", "0", "-1", "5", "-1", "0", "-1", "0"};
    MatrixFilter::Apply(image, sharpening_values);
}
