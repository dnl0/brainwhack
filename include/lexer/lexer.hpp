#pragma once

#include <vector>
#include <string>

enum lexem_type_ { comment_ = -1, ptr_op_ = 1, data_op_, input_cmd_, output_cmd_, bracket_open_, bracket_close_ };

struct token_ {
    char data;
    lexem_type_ type;

    size_t line;
    size_t column;
};

std::vector <token_> lex(const std::string& input);
