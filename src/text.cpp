#include <utils/text.hpp>

#define COLOR_PREFIX "\033"
#define RESET "\033[0m"

namespace text {
    std::string bold(std::string&& s)
    {
        return "\e[1m" + s + RESET;
    }

    std::string italic(std::string&& s)
    {
        return "\e[3m" + s + RESET;
    }

    std::string red(std::string&& s)
    {
        return COLOR_PREFIX "[31m" + s + COLOR_PREFIX RESET;
    }

    std::string green(std::string&& s)
    {
        return COLOR_PREFIX "[32m" + s + COLOR_PREFIX RESET;
    }
} // text
