/*
 * @TODO:
 *      + implement copy constructor and copy assignment operator
 *           (the necessity is questionable)
 *      + calculating return expression
 *      + function for accessing leaves of the expressions
 *      + function for accessing return values of statements
 *      + io statement
 */

#pragma once

#include "expr.hpp"
#include "scope.hpp"

enum stmt_type_ { expr_stmt_, ctrl_stmt_, io_stmt_ };

struct statement_ {
    expression_* return_expression = nullptr;

    stmt_type_ statement_type;
    bool terminated = true;
    char symbol;

    statement_() = default;

    statement_(const statement_& other) = delete;
    statement_& operator=(const statement_& other) = delete;

    virtual ~statement_()
    {
        if (return_expression) delete return_expression;
    }

    virtual statement_* back() { return nullptr; }
    virtual void emplace_back(statement_* stmt) { }
    virtual std::list <statement_*> body() { std::list <statement_*> _; return _; }
};

struct expression_statement_: statement_ {
    expression_* body_ = nullptr;

    expression_statement_(expression_* u_body, const char u_symbol)
        :
        body_ {u_body}
    {
        symbol = u_symbol;
        statement_type = expr_stmt_;
    }

    expression_statement_(const expression_statement_&) = delete;
    expression_statement_& operator=(const expression_statement_&) = delete;

    ~expression_statement_()
    {
        if (body_) delete body_;
    }
};

struct control_statement_ : statement_ {
    std::list<statement_*> body_ {};
    expression_* condition = nullptr;

    control_statement_(expression_* u_condition, statement_* u_body)
        :
        condition {u_condition},
        body_ {u_body}
    {
        symbol = '[';
        statement_type = ctrl_stmt_;
        terminated = false;
    }

    control_statement_(const control_statement_&) = delete;
    control_statement_& operator=(const control_statement_&) = delete;

    virtual void emplace_back(statement_* stmt) override { body_.emplace_back(stmt); }
    virtual statement_* back() override { return body_.back(); }
    virtual std::list <statement_*> body() override { return body_; }

    ~control_statement_()
    {
        for (auto& x: body_) { delete x; }
        if (condition) delete condition;
    }
};

struct io_statement_ : statement_ {
    // @TODO
    io_statement_(const char u_ch)
    {
        statement_type = io_stmt_;
        symbol = u_ch;
    }
};
