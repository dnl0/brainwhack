#include <parser/parser.hpp>
#include <utils/error_handling.hpp>

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

    std::shared_ptr <expression_statement_>
    create_expr_stmt(const char ch)
    {
        switch (char2type(ch)) {
            case var_plus_:
            case var_minus_:
                return  
                    std::make_shared <expression_statement_> (
                        std::make_shared <binary_operation_> (
                            std::make_shared <integer_literal_> (),
                            assign_,
                            std::make_shared <binary_operation_> (
                                std::make_shared <integer_literal_> (),
                                char2type(ch),
                                std::make_shared <integer_literal_> ()
                            )
                        ),
                        ch
                );
                break;
            case ptr_plus_:
            case ptr_minus_:
                return  
                    std::make_shared <expression_statement_> (
                        std::make_shared <binary_operation_> (
                            std::make_shared <pointer_> (),
                            assign_,
                            std::make_shared <binary_operation_> (
                                std::make_shared <pointer_> (),
                                char2type(ch),
                                std::make_shared <integer_literal_> ()
                            )
                        ),
                        ch
                );
                break;
            default: break;
        }

        return nullptr;
    }

    std::shared_ptr <control_statement_>
    create_ctrl_stmt()
    {
        return  std::make_shared <control_statement_> (
                    std::make_shared <binary_operation_> (
                        std::make_shared <integer_literal_> (),
                        not_equal_,
                        std::make_shared <integer_literal_> ()
                    ),
                    std::make_shared <statement_> ()
        );
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
    
    parser_::issue_
    add_stmt(std::vector <token_>::iterator& source_begin, 
             const std::vector <token_>::iterator& source_end,
             std::list <std::shared_ptr <statement_>>& target)
    {
        static int bracket_count = 0;
        static token_ last_opening_bracket {};

        for (; source_begin != source_end; ++source_begin) {
            switch ((*source_begin).type) {
                case bracket_open_:
                    target.emplace_back(create_ctrl_stmt());

                    ++bracket_count;
                    last_opening_bracket.line = (*source_begin).line;
                    last_opening_bracket.column = (*source_begin).column;
                    ++source_begin; // skip the bracket

                    add_stmt(source_begin, source_end, 
                             std::static_pointer_cast <control_statement_> (target.back())->body );
                    break;
                case bracket_close_:
                    if (!bracket_count) {
                        parser_::process_issue(parser_::unopened_bracket_, (*source_begin));
                    }
                    target.back()->terminated = true;

                    --bracket_count;
                    ++source_begin;

                    return parser_::none_;
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
            parser_::process_issue(parser_::unclosed_bracket_, last_opening_bracket);
        }

        return parser_::none_;
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
