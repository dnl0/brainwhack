#include <codegen/codegen.hpp>

std::string codegen(const std::vector <token>& u_data)
{
    std::string result {};
    result += "#include<stdio.h>\nchar array[1000]={0};char *ptr=array;int main(void){";
    for (auto& x: u_data) {
        if (x.m_type != comment) {
            result += x.m_cdata;
        }
    }
    result += "}";

    return result;
}
