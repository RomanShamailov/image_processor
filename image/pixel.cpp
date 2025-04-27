#include "pixel.h"

Pixel::Pixel(float red, float green, float blue) : red_(red), green_(green), blue_(blue){};

float Pixel::GetRed() const {
    return red_;
}

float Pixel::GetBlue() const {
    return blue_;
}

float Pixel::GetGreen() const {
    return green_;
}

void Pixel::SetColors(float new_red, float new_green, float new_blue) {
    if (new_red < 0 || new_red > 1) {
        throw std::runtime_error("Incorrect red value.");
        return;
    }
    if (new_green < 0 || new_green > 1) {
        throw std::runtime_error("Incorrect green value.");
        return;
    }
    if (new_blue < 0 || new_blue > 1) {
        throw std::runtime_error("Incorrect blue value.");
        return;
    }
    red_ = new_red;
    green_ = new_green;
    blue_ = new_blue;
}

Pixel operator+(const Pixel& a, const Pixel& b) {
    return Pixel(a.red_ + b.red_, a.green_ + b.green_, a.blue_ + b.blue_);
}

Pixel operator*(FourBytes n, const Pixel& p) {
    return Pixel(p.red_ * static_cast<float>(n), p.green_ * static_cast<float>(n), p.blue_ * static_cast<float>(n));
}

Pixel operator*(const Pixel& p, FourBytes n) {
    return Pixel(p.red_ * static_cast<float>(n), p.green_ * static_cast<float>(n), p.blue_ * static_cast<float>(n));
}

Pixel operator*(float n, const Pixel& p) {
    return Pixel(p.red_ * n, p.green_ * n, p.blue_ * n);
}

Pixel operator*(const Pixel& p, float n) {
    return Pixel(p.red_ * n, p.green_ * n, p.blue_ * n);
}

bool AlmostEqual(float a, float b) {
    return std::fabs(a - b) < EPSILON;
}

bool operator==(const Pixel& a, const Pixel& b) {
    return (AlmostEqual(a.red_, b.red_) && AlmostEqual(a.green_, b.green_) && AlmostEqual(a.blue_, b.blue_));
}
