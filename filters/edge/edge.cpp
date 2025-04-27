#include "edge.h"
#include <iostream>

void Edge::Apply(Image& image, std::vector<std::string>& arguments) {
    Grayscale::Apply(image, arguments);
    std::vector<std::string> edge_values = {"0", "-1", "0", "-1", "4", "-1", "0", "-1", "0"};
    MatrixFilter::Apply(image, edge_values);
    float threshold = std::stof(arguments[0]);
    for (FourBytes y = 0; y < image.GetHeight(); ++y) {
        for (FourBytes x = 0; x < image.GetWidth(); ++x) {
            if (image.GetPixel(x, y).GetRed() > threshold) {
                image.SetPixel(x, y, Pixel(1.0f, 1.0f, 1.0f));
            } else {
                image.SetPixel(x, y, Pixel(0.0f, 0.0f, 0.0f));
            }
        }
    }
}
