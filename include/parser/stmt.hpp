/*
 * @TODO:
 *      + implement copy constructor and copy assignment operator
 *           (the necessity is questionable)
 */

#pragma once

#include "expr.hpp"
#include "scope.hpp"

enum stmt_type_ { expr_stmt_, ctrl_stmt_ };

struct statement_ {
    statement_* next = nullptr;
    expression_* return_expression = nullptr;

    stmt_type_ statement_type;
    bool terminated = true;
    char symbol;

    statement_()
    {
    }

    statement_(const statement_& other) 
    {
        if (next) delete next;
        next = other.next;
        return_expression = other.return_expression;
        statement_type = other.statement_type;
        terminated = other.terminated;
    }

    statement_& operator=(const statement_& other)
    {
        if (next) delete next;
        next = other.next;
        return_expression = other.return_expression;
        statement_type = other.statement_type;
        terminated = other.terminated;

        return *this;
    }

    virtual ~statement_()
    {
        if (next) delete next;
    }

    virtual statement_* get_body() const { return nullptr; };
};

struct expression_statement_: statement_ {
    expression_* body = nullptr;

    /*expression_statement_(expression_* u_body)
        :
        body {u_body}
    {
        statement_type = expr_stmt_;
    }*/

    expression_statement_(expression_* u_body, const char u_symbol)
        :
        body {u_body}
    {
        symbol = u_symbol;
        statement_type = expr_stmt_;
    }

    ~expression_statement_()
    {
        if (body) delete body;
    }
};

struct control_statement_ : statement_ {
    statement_* body = nullptr;
    expression_* condition = nullptr;

    control_statement_(expression_* u_condition, statement_* u_body)
        :
        condition {u_condition},
        body {u_body}
    {
        symbol = '[';
        statement_type = ctrl_stmt_;
    }

    statement_* get_body() const override
    {
        return body;
    }

    ~control_statement_()
    {
        if (body) delete body;
        if (condition) delete condition;
    }
};

struct io_statement_ : statement_ {
    // @TODO
    io_statement_(const char u_ch)
    {
        symbol = u_ch;
    }
};
