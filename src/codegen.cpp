#include <codegen/codegen.hpp>

//static go_left

std::string codegen(const std::vector <token_>& u_data)
{
    std::string result {};
    result += "#include<stdio.h>\nchar array[1000]={0};char *ptr=array;int main(void){";

    for (auto& x: u_data) {
        if (x.type != comment_) {
            // result += x.m_cdata;
            // @TODO: generate C code here, and not in the lexer
        }
    }

    result += "}";
    return result;
}

/*
std::string codegen(const node_tree& u_data)
{
}
*/
