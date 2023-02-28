#include <parser/parser.hpp>
#include <utils/text.hpp>

#include <iostream>

namespace {
    op_type_
    char2type (const char ch)
    {
        switch (ch) {
            case '+':
                return var_plus_;
            case '-':
                return var_minus_;
            case '>':
                return ptr_plus_;
            case '<':
                return ptr_minus_;
        }

        return unknwn_;
    }

    expression_statement_*
    create_expr_stmt(const char ch)
    {
        switch (char2type(ch)) {
            case var_plus_:
            case var_minus_:
                return  
                    new expression_statement_ {             \
                        new binary_operation_ {             \
                            new integer_literal_ {},        \
                            assign_,                        \
                            new binary_operation_ {         \
                                new integer_literal_ {},    \
                                char2type(ch),              \
                                new integer_literal_ {}     \
                            }                               \
                        },                                  \
                        ch                                  \
                };
                break;
            case ptr_plus_:
            case ptr_minus_:
                return  
                    new expression_statement_ {             \
                        new binary_operation_ {             \
                            new pointer_ {},                \
                            assign_,                        \
                            new binary_operation_ {         \
                                new pointer_ {},            \
                                char2type(ch),              \
                                new integer_literal_ {}     \
                            }                               \
                        },                                  \
                        ch                                  \
                };
                break;
            default: break;
        }

        return nullptr;
    }

    control_statement_* 
    create_ctrl_stmt()
    {
        return  new control_statement_ {                    \
                    new binary_operation_ {                 \
                        new integer_literal_ {},            \
                        not_equal_,                         \
                        new integer_literal_ {}             \
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
                        std::cerr << red(bold("\nfatal")) << ": unopened bracket\n";
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
            std::cerr << red(bold("\nfatal")) << ": unclosed bracket\n";
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
