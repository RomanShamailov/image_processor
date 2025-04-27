#include "image.h"
#include <iostream>

FourBytes Image::GetHeight() const {
    return height_;
}

FourBytes Image::GetWidth() const {
    return width_;
}

Pixel Image::GetPixel(FourBytes x, FourBytes y) const {
    return pixel_array_[std::clamp(y, 0, height_ - 1) * width_ + std::clamp(x, 0, width_ - 1)];
}

void Image::SetPixel(FourBytes x, FourBytes y, Pixel new_pixel) {
    if (x >= width_ || x < 0 || y >= height_ || y < 0) {
        throw std::logic_error("Coordinates out of bounds.");
        return;
    }
    pixel_array_[y * width_ + x] = new_pixel;
}

void Image::SetPixelArray(FourBytes new_height, FourBytes new_width, std::vector<Pixel>& new_pixel_array) {
    if (static_cast<size_t>(new_height * new_width) != new_pixel_array.size()) {
        throw std::runtime_error("Invalid size of new array.");
    }
    height_ = new_height;
    width_ = new_width;
    pixel_array_ = std::move(new_pixel_array);
}

std::fstream FileStreamValidation(const std::string& path, std::string mode) {
    std::fstream f;
    if (mode == "input") {
        f.open(path, std::ios::in | std::ios::binary);
    } else {
        f.open(path, std::ios::out | std::ios::binary);
    }
    if (!f) {
        throw std::runtime_error("Could not open file.");
    }
    if (path.size() <= 4) {
        throw std::runtime_error("Not a BMP file.");
    } else if (path.substr(path.size() - 4, 4) != ".bmp") {
        throw std::runtime_error("Not a BMP file.");
    }
    return f;
}

FourBytes Image::CalculatePadding() const {
    return ((4 - (width_ * 3) % 4) % 4);
}

void Image::Read(const std::string& path) {
    std::fstream f = FileStreamValidation(path, "input");
    std::array<Byte, FILE_HEADER_SIZE> file_header;
    f.read(reinterpret_cast<char*>(file_header.data()), FILE_HEADER_SIZE);
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw std::runtime_error("Not a BMP file.");
    }
    FourBytes offset = 0;
    for (FourBytes i = 0; i < 4; ++i) {
        FourBytes shift = EIGHT * i;
        offset += file_header[OFFSET_INDEX + i] << shift;
    }
    if (offset != FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE) {
        throw std::runtime_error("Wrong BMP file format.");
    }
    std::array<Byte, INFORMATION_HEADER_SIZE> information_header;
    f.read(reinterpret_cast<char*>(information_header.data()), INFORMATION_HEADER_SIZE);
    FourBytes number_of_bits = information_header[BIT_INDEX] + (information_header[BIT_INDEX + 1] << EIGHT);
    FourBytes compression = 0;
    for (FourBytes i = 0; i < 4; ++i) {
        FourBytes shift = EIGHT * i;
        compression += information_header[COMPRESSION_INDEX + i] << shift;
        width_ += information_header[WIDTH_INDEX + i] << shift;
        height_ += information_header[HEIGHT_INDEX + i] << shift;
    }
    if (number_of_bits != NUMBER_OF_BITS || compression != 0) {
        throw std::runtime_error("Wrong BMP file format.");
    }
    const FourBytes padding_size = CalculatePadding();
    pixel_array_.resize(width_ * height_);
    for (FourBytes y = 0; y < height_; ++y) {
        for (FourBytes x = 0; x < width_; ++x) {
            std::array<Byte, 3> rgb_inverse;
            f.read(reinterpret_cast<char*>(rgb_inverse.data()), 3);
            SetPixel(
                x, y,
                Pixel(static_cast<float>(rgb_inverse[2]) / MAX_COLOR, static_cast<float>(rgb_inverse[1]) / MAX_COLOR,
                      static_cast<float>(rgb_inverse[0]) / MAX_COLOR));
        }
        f.ignore(padding_size);
    }
    f.close();
}

void Image::Write(const std::string& path) const {
    std::fstream f = FileStreamValidation(path, "output");
    std::array<Byte, FILE_HEADER_SIZE> file_header{};
    std::array<Byte, INFORMATION_HEADER_SIZE> information_header{};
    file_header[0] = 'B';
    file_header[1] = 'M';
    const FourBytes padding_size = CalculatePadding();
    const FourBytes file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + (3 * width_ + padding_size) * height_;
    FourBytes pixel_array_size = file_size - FILE_HEADER_SIZE - INFORMATION_HEADER_SIZE;
    for (FourBytes i = 0; i < 4; ++i) {
        FourBytes shift = EIGHT * i;
        file_header[FILE_SIZE_INDEX + i] = file_size >> shift;
        information_header[WIDTH_INDEX + i] = width_ >> shift;
        information_header[HEIGHT_INDEX + i] = height_ >> shift;
        information_header[IMAGE_SIZE_INDEX + i] = pixel_array_size >> shift;
    }
    file_header[OFFSET_INDEX] = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE;
    information_header[0] = INFORMATION_HEADER_SIZE;
    information_header[PLANE_INDEX] = NUMBER_OF_PLANES;
    information_header[BIT_INDEX] = NUMBER_OF_BITS;
    std::array<Byte, 3> padding = {'0', '0', '0'};
    f.write(reinterpret_cast<char*>(file_header.data()), FILE_HEADER_SIZE);
    f.write(reinterpret_cast<char*>(information_header.data()), INFORMATION_HEADER_SIZE);
    for (FourBytes y = 0; y < height_; ++y) {
        for (FourBytes x = 0; x < width_; ++x) {
            std::array<Byte, 3> rgb_inverse;
            rgb_inverse[2] = static_cast<Byte>(GetPixel(x, y).GetRed() * MAX_COLOR);
            rgb_inverse[1] = static_cast<Byte>(GetPixel(x, y).GetGreen() * MAX_COLOR);
            rgb_inverse[0] = static_cast<Byte>(GetPixel(x, y).GetBlue() * MAX_COLOR);
            f.write(reinterpret_cast<char*>(rgb_inverse.data()), 3);
        }
        f.write(reinterpret_cast<char*>(padding.data()), padding_size);
    }
    f.close();
}

bool operator==(const Image& a, const Image& b) {
    if (a.width_ != b.width_ || a.height_ != b.height_) {
        return false;
    } else {
        for (FourBytes y = 0; y < a.height_; ++y) {
            for (FourBytes x = 0; x < a.width_; ++x) {
                if (!(a.GetPixel(x, y) == b.GetPixel(x, y))) {
                    return false;
                }
            }
        }
    }
    return true;
}
