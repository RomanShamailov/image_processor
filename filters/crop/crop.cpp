#include "crop.h"

void Crop::Apply(Image& image, std::vector<std::string>& arguments) {
    FourBytes new_width = std::stoi(arguments[0]);
    if (new_width > image.GetWidth()) {
        new_width = image.GetWidth();
    }
    FourBytes new_height = std::stoi(arguments[1]);
    if (new_height > image.GetHeight()) {
        new_height = image.GetHeight();
    }
    std::vector<Pixel> new_pixel_array;
    for (FourBytes y = (image.GetHeight() - new_height); y < image.GetHeight(); ++y) {
        for (FourBytes x = 0; x < new_width; ++x) {
            new_pixel_array.push_back(image.GetPixel(x, y));
        }
    }
    image.SetPixelArray(new_height, new_width, new_pixel_array);
}
