/*
 * @TODO:
 *      + move to smart pointers
 *      + PTR_ should have an actual address
 */
#include <parser/parser.hpp>

#include <iostream>

#define PTR_ -1

static op_type_ char2type(const char ch)
{
    // little code duplication to 
    // avoid big code duplication
    switch (ch) {
        case '+':
        case '>':
            return plus_;
        case '-':
        case '<':
            return minus_;
    }

    return err_;
}

void* parse(const std::vector <token_> data)
{
    parse_tree* pt = new parse_tree {};

    for (auto& x: data) {
        switch (x.data) {
            case '+':
            case '-':
            case '>':
            case '<':
                pt->add_statement(                              \
                    new expression_statement_ {                 \
                        new binary_operation_ {                 \
                            new integer_literal_ {PTR_},        \
                            equal_,                             \
                            new binary_operation_ {             \
                                new integer_literal_ {PTR_},    \
                                char2type(x.data),              \
                                new integer_literal_ {1}        \
                }}});
                break;
            case '[':
                // @TODO:
                //      + go through the arguments until `]` is found,
                //          then, create the statements, and add them 
                //          to the parse tree
                pt->add_statement(                              \
                    new control_statement_ {                    \
                        new binary_operation_ {                 \
                            new integer_literal_ {PTR_},        \
                            not_equal_,                         \
                            new integer_literal_ {0}            \
                        },                                      \
                        new statement_                          \
                });
                break;
            case ']':
                break;
            case '.':
            case ',': break;
        }
    }

    return nullptr;
}
