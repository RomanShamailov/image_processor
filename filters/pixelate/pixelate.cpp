#include "pixelate.h"

// пикселизация - делает изображение блочным, разбивая его на цветные квадраты, цвет которых определяется замененными
// пикселями. intensity - длина стороны одного "блока"

void Pixelate::Apply(Image& image, std::vector<std::string>& arguments) {
    FourBytes intensity = std::stoi(arguments[0]);
    for (FourBytes y = 0; y < image.GetHeight(); y += intensity) {
        for (FourBytes x = 0; x < image.GetWidth(); x += intensity) {
            Pixel average_pixel = Pixel(0, 0, 0);
            for (FourBytes j = y; j < y + intensity; ++j) {
                for (FourBytes i = x; i < x + intensity; ++i) {
                    average_pixel = average_pixel + image.GetPixel(i, j);
                }
            }
            average_pixel = average_pixel * (1.0f / static_cast<float>((intensity * intensity)));
            for (FourBytes j = y; j < y + intensity; ++j) {
                for (FourBytes i = x; i < x + intensity; ++i) {
                    if (i >= 0 && i < image.GetWidth() && j >= 0 && j < image.GetHeight()) {
                        image.SetPixel(
                            i, j, Pixel(average_pixel.GetRed(), average_pixel.GetGreen(), average_pixel.GetBlue()));
                    }
                }
            }
        }
    }
}
