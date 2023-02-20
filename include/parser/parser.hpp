/*
 * @TODO:
 *      + finally implement parser
 *      + add bracket check
 */

#pragma once

#include <lexer/lexer.hpp>

#include "stmt.hpp"
#include "expr.hpp"

class parse_tree {
    private:
        std::vector <statement_*> data_;
    public:
        inline void add_statement(statement_* other) noexcept
        {
            data_.emplace_back(other);
        }

        ~parse_tree()
        {
            for (auto& x: data_) {
                delete x;
            }
        }
};

void* parse(const std::vector <token_> data);
