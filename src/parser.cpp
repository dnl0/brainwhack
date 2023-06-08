#include <parser/parser.hpp>
#include <utils/error_handling.hpp>

namespace { // vague builder functions
    std::shared_ptr <integer_literal_>
    build_integer_literal_expr(int value)
    {
        return std::make_shared <integer_literal_> (value);
    }

    std::shared_ptr <pointer_>
    build_pointer_expr(char* ptr = nullptr)
    {
        return std::make_shared <pointer_> (ptr);
    }

    std::shared_ptr <variable_>
    build_variable_expr(const std::string& id = "", int value = 0)
    {
        return std::make_shared <variable_> (id, value);
    }

    std::shared_ptr <binary_operation_>
    build_bin_op_expr(std::shared_ptr <expression_> left,
                      op_type_ operation,
                      std::shared_ptr <expression_> right)
    {
        return std::make_shared <binary_operation_> (left, operation, right);
    }

    std::shared_ptr <expression_statement_>
    build_expr_stmt(std::shared_ptr <expression_> body)
    {
        return std::make_shared <expression_statement_> (body);
    }

    std::shared_ptr <control_statement_>
    build_ctrl_stmt(std::shared_ptr <expression_> condition_value_left, 
                    op_type_ operation,
                    std::shared_ptr <expression_> condition_value_right)
    {
        return std::make_shared <control_statement_> (
               build_bin_op_expr(condition_value_left, operation, condition_value_right),
               std::make_shared <statement_> ());
    }

    std::shared_ptr <input_statement_>
    build_input_stmt()
    {
        return std::make_shared <input_statement_> ();
    }

    std::shared_ptr <output_statement_>
    build_output_stmt()
    {
        return std::make_shared <output_statement_> ();
    }
} // namespace

namespace { // concrete builder functions
    // while (*ptr != 0) { <body> }
    std::shared_ptr <control_statement_>
    concrete_build_bf_loop()
    {
        return build_ctrl_stmt(
                build_variable_expr(),
                not_equal_,
                build_integer_literal_expr(0));
    }

    // *ptr = *ptr <operation> <increment>
    std::shared_ptr <expression_statement_>
    concrete_build_bf_val_operation(op_type_ operation, int increment)
    {
        return build_expr_stmt(
                build_bin_op_expr(
                    build_variable_expr(),
                    operation,
                    build_integer_literal_expr(increment)));
    }

    // ptr = ptr <operation> <increment>
    std::shared_ptr <expression_statement_>
    concrete_build_bf_ptr_operation(op_type_ operation, int increment)
    {
        return build_expr_stmt(
                build_bin_op_expr(
                    build_pointer_expr(),
                    operation,
                    build_integer_literal_expr(increment)));
    }

    // user input
    std::shared_ptr <input_statement_>
    concrete_build_bf_input()
    {
        return build_input_stmt();
    }

    // print value
    std::shared_ptr <output_statement_>
    concrete_build_bf_output()
    {
        return build_output_stmt();
    }
} // namespace

namespace { // the rest
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

        int increment {};
        for (; source_begin != source_end; ++source_begin) {
            switch ((*source_begin).type) {
                case bracket_open_:
                    target.emplace_back(concrete_build_bf_loop());
                    ++bracket_count;
                    last_opening_bracket.line = (*source_begin).line;
                    last_opening_bracket.column = (*source_begin).column;
                    ++source_begin; // skip the bracket
                    // after the opening bracket add statements to the body of the
                    // control statement and exit once the closing bracket appears
                    add_stmt(source_begin, source_end, 
                            std::static_pointer_cast <control_statement_> (target.back())->body);
                    --source_begin;
                    break;
                case bracket_close_:
                    if (!bracket_count) { process_issue(unopened_bracket_, (*source_begin)); }
                    target.back()->terminated = true;
                    --bracket_count;
                    ++source_begin; // skip the bracket
                    return none_;
                case data_op_:
                    increment = squash_commands(source_begin, source_end);
                    target.emplace_back(
                        concrete_build_bf_val_operation(
                                char_to_op_type((*source_begin).data),
                                increment));
                    increment = 0;
                    break;
                case ptr_op_:
                    increment = squash_commands(source_begin, source_end);
                    target.emplace_back(
                        concrete_build_bf_ptr_operation(
                                char_to_op_type((*source_begin).data),
                                increment));
                    increment = 0;
                    break;
                case input_cmd_:
                    target.emplace_back(concrete_build_bf_input());
                    break;
                case output_cmd_:
                    target.emplace_back(concrete_build_bf_output());
                    break;
                default: break;
            }
        }

        if (bracket_count != 0) { process_issue(unclosed_bracket_, last_opening_bracket); }
        return none_;
    }
} // namespace

parse_tree
parse(std::vector <token_>&& data)
{
    parse_tree pt {};

    auto begin = data.begin();
    auto end = data.end();
    add_stmt(std::ref(begin), std::ref(end), pt.data_);

    return pt;
}
