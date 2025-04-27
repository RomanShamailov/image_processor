#include "../image/image.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

// reading two by two image

void TestCaseOne() {
    Image image;
    image.Read("./data/test_1.bmp");
    Image desired_image;
    std::vector<Pixel> pixel_array;
    pixel_array.push_back(Pixel(1.0f, 0.0f, 0.0f));
    pixel_array.push_back(Pixel(1.0f, 1.0f, 1.0f));
    pixel_array.push_back(Pixel(0.0f, 0.0f, 1.0f));
    pixel_array.push_back(Pixel(0.0f, 1.0f, 0.0f));
    desired_image.SetPixelArray(2, 2, pixel_array);
    assert(desired_image.GetWidth() == 2);
    assert(desired_image.GetHeight() == 2);
    assert(image == desired_image);
}

// reading two by four (non-square) image

void TestCaseTwo() {
    Image image;
    image.Read("./data/test_2.bmp");
    Image desired_image;
    std::vector<Pixel> pixel_array;
    pixel_array.push_back(Pixel(1.0f, 0.0f, 0.0f));
    pixel_array.push_back(Pixel(1.0f, 1.0f, 1.0f));
    pixel_array.push_back(Pixel(0.0f, 1.0f, 1.0f));
    pixel_array.push_back(Pixel(0.0f, 0.0f, 0.0f));
    pixel_array.push_back(Pixel(0.0f, 0.0f, 1.0f));
    pixel_array.push_back(Pixel(0.0f, 1.0f, 0.0f));
    pixel_array.push_back(Pixel(1.0f, 1.0f, 0.0f));
    pixel_array.push_back(Pixel(1.0f, 0.0f, 1.0f));
    desired_image.SetPixelArray(2, 4, pixel_array);
    assert(desired_image.GetWidth() == 4);
    assert(desired_image.GetHeight() == 2);
    assert(image == desired_image);
}

// wrong file formats

void TestCaseThree() {
    try {
        Image image;
        image.Read("./data/nonexistent.bmp");
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Could not open file."));
    }
    try {
        Image image;
        image.Read("./data/dummy.png");
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not a BMP file."));
    }
    try {
        Image image;
        image.Read("./data/dummy.txt");
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == "Not a BMP file.");
    }
    try {
        Image image;
        image.Read("./data/smol");
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == "Not a BMP file.");
    }
    try {
        Image image;
        image.Read("./data/large");
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == "Not a BMP file.");
    }
    try {
        Image image;
        image.Read("./data/test_1.bmp");
        image.Write("./data/nonexistent.bmp");
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Could not open file."));
    }
    try {
        Image image;
        image.Read("./data/test_1.bmp");
        image.Write("./data/smol");
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not a BMP file."));
    }
    try {
        Image image;
        image.Read("./data/test_1.bmp");
        image.Write("./data/large");
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not a BMP file."));
    }
}

int main() {
    TestCaseOne();
    TestCaseTwo();
    TestCaseThree();
    std::cout << "All tests passed." << std::endl;
}
