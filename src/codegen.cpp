#include <codegen/codegen.hpp>

std::string codegen(const std::vector <token>& u_data)
{
    std::string result {};
    result += "#include <stdio.h>\\char array[3000] = {0};\nchar *ptr = array;\nint main(void) {\n";
    for (auto& x: u_data) {
        if (x.m_type != comment) {
            result += x.m_cdata;
        }
    }
    result += "}";

    return result;
}
