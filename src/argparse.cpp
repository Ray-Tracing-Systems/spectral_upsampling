#include "argparse.h"
#include <cstring>
#include <getopt.h>
#include <iostream> 

namespace {
    enum InputType
    {
        NONE,
        COLOR,
        FILE
    };
}

bool parse_args(int argc, char **argv, Args &args)
{
    static struct option long_options[] = {
        {"downsample", 0, nullptr, 1}
    };

    InputType input_type = InputType::NONE;
    int c;
    while((c = getopt_long(argc, argv, "c:f:m:W;", long_options, nullptr)) != -1) {
        switch(c) {
        case 1:
            args.downsample_mode = true;
            break;
        case 'c':
            if(input_type != InputType::NONE) return false;
            args.color = Pixel::from_argb(std::stoi(optarg, nullptr, 16));
            input_type = InputType::COLOR;
            break;
        case 'f':
            if(input_type != InputType::NONE) return false;
            args.input_path = optarg;
            input_type = InputType::FILE;
            break;
        case 'm':
            args.method.emplace(optarg);
            break;
        case 'W':
            if(!strcmp(optarg, "downsample")) {
                args.downsample_mode = true;
            }
            break;
        case '?':
            std::cerr << "[!] Unknown argument." << std::endl; 
            return false;
        }
    }  
    if(input_type == InputType::NONE) {
        std::cerr << "[!] No input specified." << std::endl;
        return false;
    }

    if(optind < argc) {
        args.output_path.emplace(argv[optind]);
    }

    //validate
    if(args.downsample_mode) {
        return input_type == InputType::FILE && !args.output_path.has_value() && !args.method.has_value();
    }
    else {
        if(!args.method) {
            std::cerr << "[!] No method specified." << std::endl;
            return false;
        }

        return args.output_path.has_value();
    }
}