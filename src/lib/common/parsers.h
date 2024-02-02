#ifndef COMMON_PARSERS_H
#define COMMON_PARSERS_H
#include <string>
#include <sstream>

namespace spec {

    template<typename T>
    T parse(const std::string &str)
    {
        std::stringstream ss(str);
        T val;
        ss >> val;
        return val;
    }

}

#endif