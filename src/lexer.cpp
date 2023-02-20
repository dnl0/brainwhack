#include <lexer/lexer.hpp>

#include <iostream>

token_ analyze(const char data)
{
    token_ result;
    static size_t line = 1;
    static size_t column = 0;

    switch (data) {
        case '>':
            result.type = ptr_op_;
            break;
        case '<':
            result.type = ptr_op_;
            break;
        case '+':
            result.type = data_op_;
            break;
        case '-':
            result.type = data_op_;
            break;
        case '.':
            result.type = io_cmd_;
            break;
        case ',':
            result.type = io_cmd_;
            break;
        case '[':
            result.type = bracket_open_;
            break;
        case ']':
            result.type = bracket_close_;
            break;
        case '\t':
            column += 4;
            result.type = comment_;
            return result;
        case '\n':
            ++line;
            column = 0;
            result.type = comment_;
            return result;
        default:
            result.type = comment_;
            ++column;
            return result;
    }
    ++column;

    result.line = line;
    result.column = column;
    result.data = data;

    return result;
}

std::vector <token_> lex(std::string input)
{
    std::vector <token_> result {};
    for (auto& x: input) {
        result.push_back(analyze(x));
    }
    return result;
}
