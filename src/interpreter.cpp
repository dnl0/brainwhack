#include <interpreter/interpreter.hpp>
#include <iostream>

#ifndef ARRAY_CAPACITY_
#define ARRAY_CAPACITY_ 3000
#endif

namespace {
    void exec_expr(std::shared_ptr <expression_> expr, int** ptr)
    {
        if (!expr) return;

        switch (expr.get()->expression_type) {
            case bin_op_expr_:
                {
                    auto temp = std::static_pointer_cast <binary_operation_> (expr);
                    if (temp->left)  { exec_expr(temp->left, ptr);  }
                    if (temp->right) { exec_expr(temp->right, ptr); }
                    switch (temp->operation) {
                        case var_plus_:
                            **ptr = **ptr + temp->right->return_expr;
                            break;
                        case var_minus_:
                            **ptr = **ptr - temp->right->return_expr;
                            break;
                        case ptr_plus_:
                            *ptr = *ptr + temp->right->return_expr;
                            break;
                        case ptr_minus_:
                            *ptr = *ptr - temp->right->return_expr;
                            break;
                        default: break;
                    }
                }
                break;
            default: break;
        }
    }

    void exec_stmt(std::shared_ptr <statement_> stmt, int** ptr)
    {
        if (!stmt) return;

        switch (stmt.get()->statement_type) {
            case expr_stmt_:
                exec_expr(std::static_pointer_cast <expression_statement_> (stmt)->body, ptr);
                break;
            case ctrl_stmt_:
                {
                    auto temp = std::static_pointer_cast <control_statement_> (stmt);

                    while ((**ptr) != 0) {
                        for (auto& x: temp->body) { exec_stmt(x, ptr); }
                    }
                }
                break;
            case input_stmt_:
                **ptr = std::static_pointer_cast <input_statement_> (stmt)->input();
                break;
            case output_stmt_:
                std::static_pointer_cast <output_statement_> (stmt)->output(**ptr);
                break;
        }
    }

    void run(std::vector <std::shared_ptr <statement_>> data, int** ptr)
    {
        for (auto& stmt: data) {
            exec_stmt(stmt, ptr);
        }
    }
} // namespace

void interpret(const parse_tree& pt)
{
    int arr[ARRAY_CAPACITY_];
    std::fill(arr, arr+ARRAY_CAPACITY_, 0);
    int* ptr = arr;

    run(pt.data(), &ptr);
}
