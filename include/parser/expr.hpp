#pragma once

enum op_type_ { err_ = -1, plus_, minus_, equal_, not_equal_ };
enum expr_type_ { integer_literal_expr_, binary_operation_expr_ };

struct expression_ {
    expr_type_ expression_type;

    virtual ~expression_() = default;
};

struct integer_literal_ : expression_ {
    int intlit;

    integer_literal_(const int value)
        :
        intlit {value}
    {
        expression_type = integer_literal_expr_;
    }
};

struct binary_operation_ : expression_ {
    expression_* left;
    expression_* right;
    op_type_ operation;

    binary_operation_(expression_* u_left, op_type_ u_operation, expression_* u_right)
        :
        left {u_left},
        right {u_right},
        operation {u_operation}
    {
        expression_type = binary_operation_expr_;
    }

    ~binary_operation_()
    {
        if (left) delete left;
        if (right) delete right;
    }
};
