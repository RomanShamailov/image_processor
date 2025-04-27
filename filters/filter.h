#pragma once

#include "../image/image.h"
#include <string>

class Filter {
public:
    virtual ~Filter() = default;

    virtual void Apply(Image& image, std::vector<std::string>& arguments) = 0;
};
