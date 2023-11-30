#ifndef ARGPARSE_H
#define ARGPARSE_H
#include <string>
#include <optional>
#include "imageutil/pixel.h"

struct Args {
    std::optional<std::string> output_path; 
    std::optional<std::string> method; // -m
    std::optional<Pixel> color; // -c

    std::string input_path; // -f
    bool downsample_mode = false; // --downsample
};

bool parse_args(int argc, char **argv, Args &args);


#endif