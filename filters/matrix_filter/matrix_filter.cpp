#include "matrix_filter.h"

void MatrixFilter::Apply(Image& image, std::vector<std::string>& arguments) {
    int matrix[MATRIX_SIZE];
    for (FourBytes i = 0; i < MATRIX_SIZE; ++i) {
        matrix[i] = std::stoi(arguments[i]);
    }
    std::vector<Pixel> new_pixel_array;
    for (FourBytes y = 0; y < image.GetHeight(); ++y) {
        for (FourBytes x = 0; x < image.GetWidth(); ++x) {
            Pixel new_pixel = Pixel(0, 0, 0);
            new_pixel =
                image.GetPixel(x - 1, y + 1) * matrix[TOP_LEFT] + image.GetPixel(x, y + 1) * matrix[TOP_MIDDLE] +
                image.GetPixel(x + 1, y + 1) * matrix[TOP_RIGHT] + image.GetPixel(x - 1, y) * matrix[MIDDLE_LEFT] +
                image.GetPixel(x, y) * matrix[MIDDLE] + image.GetPixel(x + 1, y) * matrix[MIDDLE_RIGHT] +
                image.GetPixel(x - 1, y - 1) * matrix[BOTTOM_LEFT] + image.GetPixel(x, y - 1) * matrix[BOTTOM_MIDDLE] +
                image.GetPixel(x + 1, y - 1) * matrix[BOTTOM_RIGHT];
            new_pixel.SetColors(std::min(1.0f, std::max(0.0f, new_pixel.GetRed())),
                                std::min(1.0f, std::max(0.0f, new_pixel.GetGreen())),
                                std::min(1.0f, std::max(0.0f, new_pixel.GetBlue())));
            new_pixel_array.push_back(new_pixel);
        }
    }
    image.SetPixelArray(image.GetHeight(), image.GetWidth(), new_pixel_array);
}
