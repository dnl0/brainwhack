#pragma once

#include <iostream>

#include <lexer/lexer.hpp>

#include "stmt.hpp"
#include "expr.hpp"

class parse_tree {
    private:
        std::vector <statement_*> data;
    public:
        parse_tree() 
        {
        }

        parse_tree(const parse_tree& other)
        {
            for (int i = 0, size = other.data.size(); i < size; ++i) {
                if (data[i] && data[i] != other.data[i]) {
                    data[i] = other.data[i];
                }
            }
        }

        parse_tree& operator=(const parse_tree&) = delete;

        inline void add_statement(statement_* other) noexcept
        {
            data.emplace_back(other);
        }

        inline statement_* back() const
        {
            return data.back();
        }

        inline std::vector <statement_*>::iterator begin()
        {
            return data.begin();
        }

        inline std::vector <statement_*>::iterator end()
        {
            return data.end();
        }

        ~parse_tree()
        {
            for (auto& x: data) {
                delete x;
            }
        }
};

parse_tree parse(const std::vector <token_> data);
