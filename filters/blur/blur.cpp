#include "blur.h"

void Blur::Apply(Image& image, std::vector<std::string>& arguments) {
    float sigma = std::stof(arguments[0]);
    float normalization = static_cast<float>(1.0f / (std::sqrt(TWO * PI) * sigma));
    FourBytes kernel_size = 2 * static_cast<FourBytes>(std::floor(3 * sigma)) + 1;
    FourBytes radius = (kernel_size - 1) / 2;
    std::vector<float> kernel;
    for (FourBytes i = 0; i < kernel_size; ++i) {
        float power =
            static_cast<float>(MINUS_ONE_HALF * std::pow((static_cast<float>(std::abs(i - radius)) / sigma), 2));
        kernel.push_back(normalization * static_cast<float>(std::pow(E, power)));
    }
    std::vector<Pixel> new_pixel_array;
    new_pixel_array.reserve(image.GetHeight() * image.GetWidth());
    for (FourBytes y_0 = 0; y_0 < image.GetHeight(); ++y_0) {
        for (FourBytes x_0 = 0; x_0 < image.GetWidth(); ++x_0) {
            Pixel new_pixel = Pixel(0, 0, 0);
            FourBytes kernel_index = 0;
            for (FourBytes i = y_0 - radius; i <= y_0 + radius; ++i) {
                new_pixel = new_pixel + image.GetPixel(x_0, i) * kernel[kernel_index];
                ++kernel_index;
            }
            new_pixel_array.push_back(new_pixel);
        }
    }
    image.SetPixelArray(image.GetHeight(), image.GetWidth(), new_pixel_array);
    new_pixel_array.clear();
    for (FourBytes y_0 = 0; y_0 < image.GetHeight(); ++y_0) {
        for (FourBytes x_0 = 0; x_0 < image.GetWidth(); ++x_0) {
            Pixel new_pixel = Pixel(0, 0, 0);
            FourBytes kernel_index = 0;
            for (FourBytes i = x_0 - radius; i <= x_0 + radius; ++i) {
                new_pixel = new_pixel + image.GetPixel(i, y_0) * kernel[kernel_index];
                ++kernel_index;
            }
            new_pixel_array.push_back(new_pixel);
        }
    }
    image.SetPixelArray(image.GetHeight(), image.GetWidth(), new_pixel_array);
}
