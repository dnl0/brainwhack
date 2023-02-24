/*
 * @NOTE:
 *      - see readme.txt in include/parser
 *
 * @TODO:
 *      + resolve code duplication in add_to_ctrl_stmt and parse
 *      + add error handling for void functions
 *      + move to smart pointers
 *      + PTR_ should have an actual address
 */

#include <parser/parser.hpp>
#include <utils/text.hpp>

#include <iostream>
#include <functional>

#ifndef PTR_
#define PTR_ -1
#endif

namespace {
    op_type_ 
    char2type(const char ch)
    {
        switch (ch) {
            case '+':
            case '>':
                return plus_;
            case '-':
            case '<':
                return minus_;
        }

        std::cerr << text::bold("warn (parser)") << ": statement's symbol not found \n";
        exit(EXIT_FAILURE);
        return err_;
    }

    io_statement_*
    create_io_stmt(const char ch)
    {
        return new io_statement_ {ch};
    }

    expression_statement_* 
    create_expr_stmt(const char ch)
    {
        return  new expression_statement_ {                 \
                    new binary_operation_ {                 \
                        new integer_literal_ {PTR_},        \
                        equal_,                             \
                        new binary_operation_ {             \
                            new integer_literal_ {PTR_},    \
                            char2type(ch),                  \
                            new integer_literal_ {1}        \
                        }                                   \
                    },                                      \
                    ch                                      \
        };
    }

    control_statement_* 
    create_ctrl_stmt()
    {
        return  new control_statement_ {                    \
                    new binary_operation_ {                 \
                        new integer_literal_ {PTR_},        \
                        not_equal_,                         \
                        new integer_literal_ {0}            \
                    },                                      \
                    new statement_                          \
        };
    }

    bool 
    add_to_ctrl_stmt(std::vector <token_>::iterator& source_begin, 
                     const std::vector <token_>::iterator& source_end,
                     statement_* target)
    {
        for (; source_begin != source_end; ++source_begin) {
            switch ((*source_begin).type) {
                case bracket_open_:
                    target->emplace_back(create_ctrl_stmt());
                    ++source_begin; // skip the bracket
                    add_to_ctrl_stmt(source_begin, source_end, target->back());
                    break;
                case bracket_close_:
                    target->terminated = true;
                    ++source_begin;
                    return true;
                case io_cmd_:
                    target->emplace_back(create_io_stmt((*source_begin).data));
                    break;
                case data_op_:
                case ptr_op_:
                    target->emplace_back(create_expr_stmt((*source_begin).data));
                    break;
                default: break;
            }
        }

        std::clog << text::bold("fatal") << ": bracket's not closed\n"; // move to err handling
        exit(EXIT_FAILURE);

        return false;
    }
} // namespace

parse_tree
parse(std::vector <token_> data)
{
    parse_tree pt {};

    for (auto it = data.begin(), end = data.end(); it != end; ++it) {
        if ((*it).type != comment_) {
            switch ((*it).data) {
                case '+':
                case '-':
                case '>':
                case '<':
                    pt.add_statement(create_expr_stmt((*it).data));
                    break;
                case '[':
                    pt.add_statement(create_ctrl_stmt());
                    ++it;
                    add_to_ctrl_stmt(std::ref(it), std::ref(end), pt.back());
                    break;
                case ']':
                    std::clog << text::bold("fatal") << ": bracket's not opened\n"; // move to error handling
                    //exit(EXIT_FAILURE);
                case '.':
                case ',': 
                    pt.add_statement(create_io_stmt((*it).data));
                    break;
            }
        }
    }

    return pt;
}
