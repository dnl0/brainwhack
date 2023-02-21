/*
 * @TODO:
 *      + solve code duplication in add_to_ctrl_stmt and parse
 *      + add error handling for void and pointer functions
 *      + move to smart pointers
 *      + IO statements
 *      + PTR_ should have an actual address
 */
#include <parser/parser.hpp>

#include <iostream>

#define PTR_ -1

static op_type_ 
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

    return err_;
}

static statement_* 
go_to_last_stmt(statement_* head)
{
    while (head->next) {
        head = head->next;
    }

    return head;
}

static void 
create_io_stmt()
{
    // @TODO
}

static expression_statement_* 
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
                    }
                },
                ch
    };
}

static control_statement_* 
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

static bool 
add_to_ctrl_stmt(std::vector <token_>::iterator source_begin, 
                 const std::vector <token_>::iterator source_end,
                 statement_* target)
{
    statement_* target_ref = target;

    for (; source_begin != source_end; ++source_begin) {
        switch ((*source_begin).data) {
            case '[':
                target->next = create_ctrl_stmt();
                target->next->terminated = false;
                target->symbol = '[';
                add_to_ctrl_stmt(source_begin, source_end, target->next);
                break;
            case ']':
                target_ref->terminated = true;
                return true;
            case '.':
            case ',':
                // @TODO
                break;
            default:
                target->next = create_expr_stmt(char2type((*source_begin).data));
                target->symbol = (*source_begin).data;
                target = target->next;
                break;
        }
    }
    
    return false;
}

parse_tree
parse(std::vector <token_> data)
{
    parse_tree pt {};

    for (auto it = data.begin(), end = data.end(); it != end; ++it) {
        switch ((*it).data) {
            case '+':
            case '-':
            case '>':
            case '<':
                pt.add_statement(create_expr_stmt((*it).data));
                break;
            case '[':
                pt.add_statement( create_ctrl_stmt() );
                ++it;
                add_to_ctrl_stmt(it, end, pt.back());
                break;
            case '.':
            case ',': 
                // @TODO
                break;
        }
    }

    return pt;
}
