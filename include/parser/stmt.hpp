#pragma once

#include <memory>
#include <functional>

#include "expr.hpp"

enum stmt_type_ { expr_stmt_ = 1, ctrl_stmt_, input_stmt_, output_stmt_ };

struct statement_ {
    std::shared_ptr <expression_> return_expression; // @TODO
    stmt_type_ statement_type;
    bool terminated;
};

struct expression_statement_ : statement_ {
    std::shared_ptr <expression_> body = nullptr;

    expression_statement_(std::shared_ptr <expression_> u_body)
        :
        body {std::move(u_body)}
    {
        statement_type = expr_stmt_;
        terminated = true;
    }
};

struct control_statement_ : statement_ {
    std::vector <std::shared_ptr <statement_>> body;
    std::shared_ptr <expression_> condition;

    control_statement_(std::shared_ptr <expression_> u_condition, 
                       std::shared_ptr <statement_> u_body)
        :
        condition {std::move(u_condition)}
    {
        body.emplace_back(std::move(u_body));
        statement_type = ctrl_stmt_;
        terminated = false;
    }
};

struct input_statement_: statement_ {
    std::function <int(void)> input  = &std::getchar;

    input_statement_()
    {
        statement_type = output_stmt_;
    }
};

struct output_statement_: statement_ {
    std::function <int(int)> output = &std::putchar;

    output_statement_()
    {
        statement_type = output_stmt_;
    }
};
