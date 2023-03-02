#pragma once

#include <lexer/lexer.hpp>

#include <list>

#include "stmt.hpp"

class parse_tree {
    private:
        std::list <std::shared_ptr <statement_>> data_ {}; // shared_ptr to make casting easier
    public:
        parse_tree() = default;

        inline std::list <std::shared_ptr <statement_>>& data()           { return data_; };
        inline std::shared_ptr <statement_> back() const                  { return data_.back(); }
        inline std::list <std::shared_ptr <statement_>>::iterator begin() { return data_.begin(); }
        inline std::list <std::shared_ptr <statement_>>::iterator end()   { return data_.end(); }
};

parse_tree parse(const std::vector <token_> data);
