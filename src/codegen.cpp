#include <codegen/codegen.hpp>

#include <string>

namespace {
    void
    append_code(std::shared_ptr <expression_> expr, std::string& target)
    {
        if (!expr) return;

        switch (expr.get()->expression_type) {
            case bin_op_expr_:
                {
                    auto temp = std::static_pointer_cast <binary_operation_> (expr);
                    if (temp->left)  { append_code(temp->left, target);  }
                    if (temp->right) { append_code(temp->right, target); }
                    switch (temp->operation) {
                        case var_plus_:
                            target += "*ptr = *ptr + " + 
                                std::to_string(std::static_pointer_cast <integer_literal_> (temp->right)->intlit) + ";";
                            break;
                        case var_minus_:
                            target += "*ptr = *ptr - " + 
                                std::to_string(std::static_pointer_cast <integer_literal_> (temp->right)->intlit) + ";";
                            break;
                        case ptr_plus_:
                            target += "ptr = ptr + " + 
                                std::to_string(std::static_pointer_cast <integer_literal_> (temp->right)->intlit) + ";";
                            break;
                        case ptr_minus_:
                            target += "ptr = ptr - " + 
                                std::to_string(std::static_pointer_cast <integer_literal_> (temp->right)->intlit) + ";";
                            break;
                        default: break;
                    }
                }
                break;
            default: break;
        }
    }

    void
    append_code(std::shared_ptr <statement_> source, std::string& target)
    {
        switch (source.get()->statement_type) {
            case expr_stmt_:
                append_code(std::static_pointer_cast <expression_statement_> (source)->body, target);
                break;
            case ctrl_stmt_:
                target += "while(*ptr != 0) {";
                {
                    auto temp = std::static_pointer_cast <control_statement_> (source);

                    for (auto& x: temp->body) { append_code(x, target); }
                }
                target += "}";
                break;
            case input_stmt_:
                target += "getchar(*ptr);";
                break;
            case output_stmt_:
                target += "putchar(*ptr);";
                break;
        }
    }
} // namespace

std::string 
codegen(parse_tree pt)
{
    std::string result {};
    result += "#include<stdio.h>\nchar array[1000]={0};char *ptr=array;int main(void){";

    for (auto& x: pt.data()) {
        append_code(x, result);
    }

    result += "}";
    return result;
}
