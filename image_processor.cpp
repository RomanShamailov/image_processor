#include "parser.h"
#include <string>
#include <vector>

int main(FourBytes argc, char* argv[]) {
    try {
        std::vector<std::string> argument_values;
        argument_values.reserve(argc);
        for (FourBytes i = 0; i < argc; ++i) {
            argument_values.push_back(argv[i]);
        }
        Parse(argc, argument_values);
    } catch (const std::exception& e) {
        std::string error_message = e.what();
        if (error_message == "stoi" || error_message == "stof") {
            std::cout << "Wrong argument format." << std::endl;
        } else {
            std::cout << error_message << std::endl;
        }
    }
}
