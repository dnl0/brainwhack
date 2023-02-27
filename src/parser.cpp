#include <parser/parser.hpp>
#include <utils/text.hpp>

#include <iostream>

#ifndef PTR_
#define PTR_ -1
#endif

namespace {
    op_type_
    char2type (const char ch)
    {
        switch (ch) {
            case '+':
            case '-':
                return plus_;
            case '>':
            case '<':
                return minus_;
        }

        return unknwn_;
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

    input_statement_*
    create_in_stmt(const char ch = ',')
    {
        return new input_statement_ {ch};
    }

    output_statement_*
    create_out_stmt(const char ch = '.')
    {
        return new output_statement_ {ch};
    }
    
    bool 
    add_stmt(std::vector <token_>::iterator& source_begin, 
             const std::vector <token_>::iterator& source_end,
             std::list <statement_*>& target)
    {
        static int bracket_count = 0;

        for (; source_begin != source_end; ++source_begin) {
            switch ((*source_begin).type) {
                case bracket_open_:
                    target.emplace_back(create_ctrl_stmt());
                    ++bracket_count;
                    ++source_begin; // skip the bracket

                    add_stmt(source_begin, source_end, 
                             static_cast <control_statement_*> (target.back())->body );
                    break;
                case bracket_close_:
                    if (!bracket_count) {
                        std::cerr << text::bold("fatal") << ": unopened bracket\n";
                        exit(EXIT_FAILURE);
                    }
                    target.back()->terminated = true;
                    --bracket_count;
                    ++source_begin;
                    return true;
                case data_op_:
                case ptr_op_:
                    target.emplace_back(create_expr_stmt((*source_begin).data));
                    break;
                case input_cmd_:
                    target.emplace_back(create_in_stmt((*source_begin).data));
                    break;
                case output_cmd_:
                    target.emplace_back(create_out_stmt((*source_begin).data));
                    break;
                default: break;
            }
        }

        if (bracket_count) {
            std::cerr << text::bold("fatal") << ": unclosed bracket\n";
            exit(EXIT_FAILURE);
            return false;
        }

        return true;
    }
} // namespace

parse_tree
parse(std::vector <token_> data)
{
    parse_tree pt {};

    auto begin = data.begin();
    auto end = data.end();
    add_stmt(std::ref(begin), std::ref(end), pt.data());

    return pt;
}
