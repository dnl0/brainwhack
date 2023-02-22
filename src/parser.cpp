/*
 * @TODO:
 *      + solve code duplication in add_to_ctrl_stmt and parse
 *      + add error handling for void and pointer functions
 *      + move to smart pointers
 *      + IO statements
 *      + PTR_ should have an actual address
 */
#include <parser/parser.hpp>
#include <utils/text.hpp>

#include <functional>

#ifndef PTR_
#define PTR_ -1
#endif

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

    /*
     * here is passed some empty characters, for some reason, but despite that 
     * the parser still gives the appropriate result
     * std::cerr << text::bold("fatal (parser)") << ": symbol '" << ch << "' (ascii: " << int(ch) << ") is not an operator\n"
              << text::bold("hint") << ": iterator invalidation might have occured\n";
    exit(EXIT_FAILURE);
    */
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

static io_statement_*
create_io_stmt(const char ch)
{
    return new io_statement_ {ch};
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
                    }                                   \
                },                                      \
                ch                                      \
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
add_to_ctrl_stmt(std::vector <token_>::iterator& source_begin, 
                 const std::vector <token_>::iterator& source_end,
                 statement_* target)
{
    statement_* target_ref = target;

    for (; source_begin != source_end; ++source_begin) {
        switch ((*source_begin).data) {
            case '[':
                target->next = create_ctrl_stmt();
                target->next->terminated = false;
                add_to_ctrl_stmt(source_begin, source_end, target->next);
                break;
            case ']':
                target_ref->terminated = true;
                ++source_begin;
                target = target_ref;
                return true;
            case '.':
            case ',':
                target->next = create_io_stmt((*source_begin).data);
                target = target->next;
                break;
            default:
                target->next = create_expr_stmt(char2type((*source_begin).data));
                target->next->symbol = (*source_begin).data;
                target = target->next;
                break;
        }
    }
    
    std::clog << text::bold("fatal") << ": bracket's not closed\n"; // move to error handling
    exit(EXIT_FAILURE);
    return false;
}

parse_tree
parse(std::vector <token_> data)
{
    parse_tree pt {};

    /*
     * @NOTE: the approach will not work since when resizing a vector
     *           an effect called "iterator invalidation occurs", and
     *           therefore passing an iterator to function is useless
     */
    for (auto it = data.begin(), end = data.end(); it != end; ++it) {
        switch ((*it).data) {
            case '+':
            case '-':
            case '>':
            case '<':
                pt.add_statement(create_expr_stmt((*it).data));
                break;
            case '[':
                pt.add_statement(create_ctrl_stmt());
                std::advance(it, 1);
                add_to_ctrl_stmt(std::ref(it), std::ref(end), pt.back());
                break;
            case ']':
                std::clog << text::bold("fatal") << ": bracket's not opened\n"; // move to error handling
                exit(EXIT_FAILURE);
            case '.':
            case ',': 
                pt.add_statement(create_io_stmt((*it).data));
                break;
        }
    }

    return pt;
}
