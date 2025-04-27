#include "../parser.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

const float FULL_COLOR = 1.0f;
const float HALF_COLOR = 0.5f;
const float NO_COLOR = 0.0f;

void TestCrop() {
    try {
        StringVector arguments;
        StringVector argument_values = {"-crop", "-1", "1"};
        FourBytes i = 0;
        CreateFilter("-crop", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"-crop", "1", "-1"};
        FourBytes i = 0;
        CreateFilter("-crop", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"-crop", "-1", "-1"};
        FourBytes i = 0;
        CreateFilter("-crop", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"-crop", "0", "1"};
        FourBytes i = 0;
        CreateFilter("-crop", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"-crop", "1", "0"};
        FourBytes i = 0;
        CreateFilter("-crop", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    {
        Image image;
        image.Read("./data/test_1.bmp");
        Image desired_image;
        std::vector<Pixel> pixel_array;
        pixel_array.push_back(Pixel(FULL_COLOR, NO_COLOR, NO_COLOR));
        pixel_array.push_back(Pixel(FULL_COLOR, FULL_COLOR, FULL_COLOR));
        pixel_array.push_back(Pixel(NO_COLOR, NO_COLOR, FULL_COLOR));
        pixel_array.push_back(Pixel(NO_COLOR, FULL_COLOR, NO_COLOR));
        desired_image.SetPixelArray(2, 2, pixel_array);
        assert(desired_image.GetHeight() == 2);
        assert(desired_image.GetWidth() == 2);
        Crop filter;
        StringVector arguments = {"5", "5"};
        filter.Apply(image, arguments);
        assert(image == desired_image);
    }
}

void TestEdge() {
    try {
        StringVector arguments;
        StringVector argument_values = {"-edge", "-1"};
        FourBytes i = 0;
        CreateFilter("-edge", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
}

void TestBlur() {
    try {
        StringVector arguments;
        StringVector argument_values = {"-blur", "0"};
        FourBytes i = 0;
        CreateFilter("-blur", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"-blur", "-1"};
        FourBytes i = 0;
        CreateFilter("-blur", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
}

void TestPixelate() {
    try {
        StringVector arguments;
        StringVector argument_values = {"-pixelate", "-0"};
        FourBytes i = 0;
        CreateFilter("-pixelate", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"-pixelate", "-1"};
        FourBytes i = 0;
        CreateFilter("-pixelate", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    Image image;
    image.Read("./data/test_2.bmp");
    Image desired_image;
    std::vector<Pixel> pixel_array;
    for (FourBytes y = 0; y < 2; ++y) {
        for (FourBytes x = 0; x < 4; ++x) {
            pixel_array.push_back(Pixel(HALF_COLOR, HALF_COLOR, HALF_COLOR));
        }
    }
    desired_image.SetPixelArray(2, 4, pixel_array);
    assert(desired_image.GetWidth() == 4);
    assert(desired_image.GetHeight() == 2);
    Pixelate filter;
    StringVector arguments = {"2"};
    filter.Apply(image, arguments);
    assert(image == desired_image);
}

int main() {
    TestCrop();
    TestEdge();
    TestBlur();
    TestPixelate();
    std::cout << "All tests passed." << std::endl;
}
