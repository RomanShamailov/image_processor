#include "parser.h"

std::unique_ptr<Filter> CreateFilter(const std::string& option, StringVector& arguments, StringVector& argument_values,
                                     FourBytes& i) {
    if (option == "-crop") {
        if (static_cast<size_t>(i + 1) >= argument_values.size() ||
            static_cast<size_t>(i + 2) >= argument_values.size()) {
            throw std::runtime_error("Not enough arguments.");
        }
        FourBytes new_width = 0;
        FourBytes new_height = 0;
        try {
            new_width = std::stoi(argument_values[i + 1]);
        } catch (std::exception& e) {
            throw std::runtime_error("Invalid argument format.");
        }
        try {
            new_height = std::stoi(argument_values[i + 2]);
        } catch (std::exception& e) {
            throw std::runtime_error("Invalid argument format.");
        }
        if (new_width <= 0) {
            throw std::runtime_error("Invalid argument format.");
        }
        if (new_height <= 0) {
            throw std::runtime_error("Invalid argument format.");
        }
        arguments.push_back(argument_values[i + 1]);
        arguments.push_back(argument_values[i + 2]);
        i += 3;
        return std::make_unique<Crop>();
    } else if (option == "-gs") {
        i += 1;
        return std::make_unique<Grayscale>();
    } else if (option == "-neg") {
        i += 1;
        return std::make_unique<Negative>();
    } else if (option == "-sharp") {
        i += 1;
        return std::make_unique<Sharpening>();
    } else if (option == "-edge") {
        if (static_cast<size_t>(i + 1) >= argument_values.size()) {
            throw std::runtime_error("Not enough arguments.");
        }
        float threshold = NAN;
        try {
            threshold = std::stof(argument_values[i + 1]);
        } catch (std::exception& e) {
            throw std::runtime_error("Invalid argument format.");
        }
        if (threshold < 0) {
            throw std::runtime_error("Invalid argument format.");
        }
        arguments.push_back(argument_values[i + 1]);
        i += 2;
        return std::make_unique<Edge>();
    } else if (option == "-blur") {
        if (static_cast<size_t>(i + 1) >= argument_values.size()) {
            throw std::runtime_error("Not enough arguments.");
        }
        float sigma = NAN;
        try {
            sigma = std::stof(argument_values[i + 1]);
        } catch (std::exception& e) {
            throw std::runtime_error("Invalid argument format.");
        }
        if (sigma <= 0) {
            throw std::runtime_error("Invalid argument format.");
        }
        arguments.push_back(argument_values[i + 1]);
        i += 2;
        return std::make_unique<Blur>();
    } else if (option == "-pixelate") {
        if (static_cast<size_t>(i + 1) >= argument_values.size()) {
            throw std::runtime_error("Not enough arguments.");
        }
        FourBytes intensity = 0;
        try {
            intensity = std::stoi(argument_values[i + 1]);
        } catch (std::exception& e) {
            throw std::runtime_error("Invalid argument format.");
        }
        if (intensity < 1) {
            throw std::runtime_error("Invalid argument format.");
        }
        arguments.push_back(argument_values[i + 1]);
        i += 2;
        return std::make_unique<Pixelate>();
    } else {
        throw std::runtime_error("Nonexistent filter.");
    }
}

void ValidateMinimalArguments(FourBytes argc, StringVector& argument_values) {
    if (argc == 1) {
        throw std::runtime_error("No arguments given.");
    }
    if (argc == 2) {
        throw std::runtime_error("No output path given.");
    }
    if (argc == 3) {
        throw std::runtime_error("No filters given.");
    }
}

void Parse(FourBytes argc, StringVector& argument_values) {
    ValidateMinimalArguments(argc, argument_values);
    std::string read_path = argument_values[1];
    std::string write_path = argument_values[2];
    Image image;
    image.Read(read_path);
    FourBytes i = 3;
    while (i < argc) {
        if (argument_values[i][0] == '-') {
            std::string option = argument_values[i];
            StringVector arguments;
            std::unique_ptr<Filter> filter = CreateFilter(option, arguments, argument_values, i);
            filter->Apply(image, arguments);
        } else {
            throw std::runtime_error("Not a filter.");
        }
    }
    image.Write(write_path);
}
