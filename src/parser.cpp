#include <parser/parser.hpp>
#include <utils/error_handling.hpp>

#include <iostream>

namespace {
    op_type_
    char_to_op_type (const char ch)
    {
        switch (ch) {
            case '+': return var_plus_;
            case '-': return var_minus_;
            case '>': return ptr_plus_;
            case '<': return ptr_minus_;
        }
        return unknwn_;
    }

    // concrete builder of a variable value/pointer expression
    // (`*ptr = *ptr + 1` or `ptr = ptr + 1`)
    std::shared_ptr <expression_statement_>
    create_expr_stmt(op_type_ type, const int& value = 1)
    {
        switch (type) {
            case var_plus_:
            case var_minus_:
                // create a variable value binary operation
                return  
                    std::make_shared <expression_statement_> (
                        std::make_shared <binary_operation_> (
                            std::make_shared <variable_> (),
                            assign_,
                            std::make_shared <binary_operation_> (
                                std::make_shared <variable_> (),
                                type,
                                std::make_shared <integer_literal_> (value)
                )));
            case ptr_plus_:
            case ptr_minus_:
                // create a pointer binary operation
                return  
                    std::make_shared <expression_statement_> (
                        std::make_shared <binary_operation_> (
                            std::make_shared <pointer_> (),
                            assign_,
                            std::make_shared <binary_operation_> (
                                std::make_shared <pointer_> (),
                                type,
                                std::make_shared <integer_literal_> (value)
                )));
            default: break;
        }

        return nullptr;
    }

    // concrete builder of a while loop (`while (*ptr != 0)`)
    std::shared_ptr <control_statement_>
    create_ctrl_stmt(const int& value = 1)
    {
        return  
            std::make_shared <control_statement_> (
                std::make_shared <binary_operation_> (
                    std::make_shared <integer_literal_> (value),
                    not_equal_,
                    std::make_shared <integer_literal_> (0)
                ),
                std::make_shared <statement_> ()
        );
    }

    input_statement_*
    create_in_stmt()
    {
        return new input_statement_ {};
    }

    output_statement_*
    create_out_stmt()
    {
        return new output_statement_ {};
    }

    int 
    squash_commands(std::vector <token_>::iterator& source_begin,
                    const std::vector <token_>::iterator& source_end)
    {
        int result {1};
        while (source_begin+1 != source_end &&
               (*source_begin).type == ((*std::next(source_begin, 1)).type)) {
            std::advance(source_begin, 1);
            ++result;
        }
        return result;
    }
    
    parser_::issue_
    add_stmt(std::vector <token_>::iterator& source_begin, 
             const std::vector <token_>::iterator& source_end,
             std::vector <std::shared_ptr <statement_>>& target)
    {
        using namespace parser_; // for error processing
        static int bracket_count = 0;
        static token_ last_opening_bracket {};

        int inc {1};
        for (; source_begin != source_end; ++source_begin) {
            switch ((*source_begin).type) {
                case bracket_open_:
                    target.emplace_back(create_ctrl_stmt());
                    ++bracket_count;
                    last_opening_bracket.line = (*source_begin).line;
                    last_opening_bracket.column = (*source_begin).column;
                    ++source_begin; // skip the bracket
                    // after the opening bracket add statements to the body of the
                    // control statement and exit once the closing bracket appears
                    add_stmt(source_begin, source_end, 
                            std::static_pointer_cast <control_statement_> (target.back())->body);
                    break;
                case bracket_close_:
                    if (!bracket_count) { process_issue(unopened_bracket_, (*source_begin)); }
                    target.back()->terminated = true;
                    --bracket_count;
                    ++source_begin; // skip the bracket
                    return none_;
                case data_op_:
                case ptr_op_:
                    // do something to inc
                    inc = squash_commands(source_begin, source_end);
                    target.emplace_back(
                        create_expr_stmt(char_to_op_type((*source_begin).data), inc));
                    inc = 1;
                    break;
                case input_cmd_:
                    target.emplace_back(create_in_stmt());
                    break;
                case output_cmd_:
                    target.emplace_back(create_out_stmt());
                    break;
                default: break;
            }
        }

        if (bracket_count != 0) { process_issue(unclosed_bracket_, last_opening_bracket); }
        return none_;
    }
} // namespace

parse_tree
parse(std::vector <token_> data)
{
    parse_tree pt {};

    auto begin = data.begin();
    auto end = data.end();
    add_stmt(std::ref(begin), std::ref(end), pt.data_);

    return pt;
}
