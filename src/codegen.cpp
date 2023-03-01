#include <codegen/codegen.hpp>

namespace {
    std::string
    bf_to_c(const char ch)
    {
        switch (ch) {
            case '>':
                return "++ptr;";
            case '<':
                return "--ptr;";
            case '+':
                return "++*ptr;";
            case '-':
                return "--*ptr;";
            case '.':
                return "putchar(*ptr);";
            case ',':
                return "*ptr = getchar();";
            case '[':
                return "while(*ptr != 0){";
            case ']':
                return "}";
            default: break;
        }

        return "";
    }

    void 
    append_code(std::list <std::shared_ptr <statement_>> source, std::string& target)
    {
        for (auto& x: source) {
            target += bf_to_c((*x).id);
            if ((*x).statement_type == ctrl_stmt_) {
                if (std::static_pointer_cast <control_statement_> (x)->body.size() > 0) {
                    append_code(std::static_pointer_cast <control_statement_> (x)->body, target);
                    target += "}";
                }
            }
        }
    }
} // namespace

std::string 
codegen(parse_tree&& pt)
{
    std::string result {};
    result += "#include<stdio.h>\nchar array[1000]={0};char *ptr=array;int main(void){";

    append_code(pt.data(), result);

    result += "}";
    return result;
}
