#pragma once

#include <cmath>
#include <cstdint>
#include <stdexcept>

using Byte = std::uint8_t;
using FourBytes = std::int32_t;

const float EPSILON = 1e-2f;

bool AlmostEqual(float a, float b);

class Pixel {
private:
    float red_;
    float green_;
    float blue_;

public:
    Pixel() = default;

    Pixel(float red, float green, float blue);

    float GetRed() const;

    float GetBlue() const;

    float GetGreen() const;

    void SetColors(float new_red, float new_green, float new_blue);

    friend Pixel operator+(const Pixel& a, const Pixel& b);

    friend Pixel operator*(FourBytes n, const Pixel& p);

    friend Pixel operator*(const Pixel& p, FourBytes n);

    friend Pixel operator*(float n, const Pixel& p);

    friend Pixel operator*(const Pixel& p, float n);

    friend bool operator==(const Pixel& a, const Pixel& b);
};
