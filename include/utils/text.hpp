#pragma once

namespace text {
    std::string bold(const std::string& s)
    {
        return "\e[1m" + s + "\e[0m";
    }

    std::string italic(const std::string& s)
    {
        return "\e[3m" + s + "\e[0m";
    }
}
