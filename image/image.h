#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <stdexcept>
#include <fstream>
#include "pixel.h"
#include <string>
#include <utility>
#include <vector>

const FourBytes FILE_HEADER_SIZE = 14;
const FourBytes INFORMATION_HEADER_SIZE = 40;
const FourBytes NUMBER_OF_PLANES = 1;
const FourBytes NUMBER_OF_BITS = 24;
const FourBytes EIGHT = 8;
const FourBytes FILE_SIZE_INDEX = 2;
const FourBytes WIDTH_INDEX = 4;
const FourBytes HEIGHT_INDEX = 8;
const FourBytes OFFSET_INDEX = 10;
const FourBytes PLANE_INDEX = 12;
const FourBytes COMPRESSION_INDEX = 16;
const FourBytes IMAGE_SIZE_INDEX = 20;
const FourBytes BIT_INDEX = 14;
const float MAX_COLOR = 255.0f;

class Image {
private:
    FourBytes height_ = 0;
    FourBytes width_ = 0;
    std::vector<Pixel> pixel_array_;

public:
    Image() = default;

    FourBytes GetHeight() const;

    FourBytes GetWidth() const;

    Pixel GetPixel(FourBytes x, FourBytes y) const;

    void SetPixel(FourBytes x, FourBytes y, Pixel new_pixel);

    void SetPixelArray(FourBytes new_height, FourBytes new_width, std::vector<Pixel>& new_pixel_array);

    FourBytes CalculatePadding() const;

    void Read(const std::string& path);

    void Write(const std::string& path) const;

    friend bool operator==(const Image& c1, const Image& c2);
};

std::fstream FileStreamValidation(const std::string& path);
