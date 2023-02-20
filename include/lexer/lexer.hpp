#pragma once

#include <vector>
#include <string>

enum lexem_type_ { comment_ = -1, ptr_op_, data_op_, io_cmd_, bracket_open_, bracket_close_ };

struct token_ {
    char data;
    lexem_type_ type;

    size_t line;
    size_t column;
};

std::vector <token_> lex(std::string input);
