#pragma once

#include <list>

#include <lexer/lexer.hpp>

#include "stmt.hpp"

class parse_tree {
    private:
        std::list <statement_*> data_ {};
    public:
        parse_tree() = default;

        parse_tree(const parse_tree& other) = delete;
        parse_tree& operator=(const parse_tree& other) = delete;

        friend void swap(parse_tree& left, parse_tree& right)
        {
            using std::swap;

            swap(left.data_, right.data_);
        }

        parse_tree(parse_tree&& other)
        {
            swap(*this, other);
        }

        inline std::list <statement_*>& data()              { return data_; };
        inline statement_* back() const                     { return data_.back(); }
        inline std::list <statement_*>::iterator begin()    { return data_.begin(); }
        inline std::list <statement_*>::iterator end()      { return data_.end(); }

        ~parse_tree()
        {
            for (auto& x: data_) { delete x; }
        }
};

parse_tree parse(const std::vector <token_> data);
