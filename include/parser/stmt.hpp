/*
 * @TODO:
 *      + implement copy constructor and copy assignment operator
 *           (questionable if necessary)
 */

#pragma once

#include "expr.hpp"

enum stmt_type_ { expr_stmt_, ctrl_stmt_ };

struct statement_ {
    statement_* next;
    expression_* return_expression;

    stmt_type_ statement_type;
    bool terminated_ = true;

    /*virtual void create_body();
    virtual void get_return();
    virtual int  return_bool() const;*/
};

struct expression_statement_: statement_ {
    expression_* body;

    expression_statement_(expression_* u_body)
        :
        body {u_body}
    {
        statement_type = expr_stmt_;
    }
};

struct control_statement_ : statement_ {
    statement_* body;
    expression_* condition;

    control_statement_(expression_* u_condition, statement_* u_body)
        :
        condition {u_condition},
        body {u_body}
    {
        statement_type = ctrl_stmt_;
    }
};
