#pragma once

#include "expr.hpp"

enum stmt_type_ { expr_stmt_, ctrl_stmt_, input_stmt_, output_stmt_ };

struct statement_ {
    expression_* return_expression;

    stmt_type_ statement_type;

    bool terminated;
    char id;
};

struct expression_statement_ : statement_ {
    expression_* body = nullptr;

    expression_statement_(expression_* u_body, const char u_id = '\0')
        :
        body {u_body}
    {
        statement_type = expr_stmt_;
        terminated = true;
        id = u_id; // this id char is used for debugging,
                   // and has no usage in regular flow
    }

    expression_statement_(const expression_statement_&) = delete;
    expression_statement_& operator=(const expression_statement_&) = delete;

    ~expression_statement_()
    {
        if (return_expression) delete return_expression;
        if (body) delete body;
    }
};

struct control_statement_ : statement_ {
    std::list <statement_*> body {};
    expression_* condition;

    control_statement_(expression_* u_condition, statement_* u_body, const char u_id = '[')
        :
        condition {u_condition},
        body {u_body}
    {
        id = u_id;
        statement_type = ctrl_stmt_;
        terminated = false;
    }
};

struct input_statement_: statement_ {
    // @TODO
    std::function <int(void)> input  = &std::getchar;

    input_statement_(const char u_id = ',')
    {
        statement_type = output_stmt_;
        id = u_id;
    }
};

struct output_statement_: statement_ {
    // @TODO
    std::function <int(int)> output = &std::putchar;

    output_statement_(const char u_id = '.')
    {
        statement_type = input_stmt_;
        id = u_id;
    }
};
