#include "../parser.h"
#include <cassert>

const FourBytes SEVEN = 7;

void TestMinimalArguments() {
    try {
        StringVector argument_values = {"./image_processor"};
        Parse(1, argument_values);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("No arguments given."));
    }
    try {
        StringVector argument_values = {"./image_processor", "test_1.bmp"};
        Parse(2, argument_values);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("No output path given."));
    }
    try {
        StringVector argument_values = {"./image_processor", "./data/test_1.bmp", "result.bmp"};
        Parse(3, argument_values);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("No filters given."));
    }
}

void TestFilter() {
    try {
        StringVector argument_values = {"./image_processor", "./data/test_1.bmp", "result.bmp", "neg"};
        Parse(4, argument_values);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not a filter."));
    }
    try {
        StringVector argument_values = {
            "./image_processor", "./data/test_1.bmp", "result.bmp", "-crop", "1", "1", "neg"};
        Parse(SEVEN, argument_values);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not a filter."));
    }
}

void TestCreateFilter() {
    try {
        StringVector arguments;
        StringVector argument_values;
        FourBytes i = 0;
        CreateFilter("-nonexistent", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Nonexistent filter."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"-crop"};
        FourBytes i = 0;
        CreateFilter("-crop", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not enough arguments."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"-crop", "1"};
        FourBytes i = 0;
        CreateFilter("-crop", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not enough arguments."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"-crop", "1", "s"};
        FourBytes i = 0;
        CreateFilter("-crop", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"edge"};
        FourBytes i = 0;
        CreateFilter("-edge", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not enough arguments."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"edge", "s"};
        FourBytes i = 0;
        CreateFilter("-edge", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Invalid argument format."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"blur"};
        FourBytes i = 0;
        CreateFilter("-blur", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not enough arguments."));
    }
    try {
        StringVector arguments;
        StringVector argument_values = {"pixelate"};
        FourBytes i = 0;
        CreateFilter("-pixelate", arguments, argument_values, i);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        assert(error_message == static_cast<std::string>("Not enough arguments."));
    }
}

int main() {
    TestMinimalArguments();
    TestFilter();
    TestCreateFilter();
    std::cout << "All tests passed." << std::endl;
}
