#pragma once

#include "./filters/blur/blur.h"
#include "./filters/crop/crop.h"
#include "./filters/edge/edge.h"
#include "./filters/grayscale/grayscale.h"
#include "./filters/negative/negative.h"
#include "./filters/pixelate/pixelate.h"
#include "./filters/sharpening/sharpening.h"
#include "./image/image.h"
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

std::unique_ptr<Filter> CreateFilter(const std::string& option, StringVector& arguments, StringVector& argument_values,
                                     FourBytes& i);

void ValidateMinimalArguments(FourBytes argc, StringVector& argument_values);

void Parse(FourBytes argc, StringVector& argument_values);
